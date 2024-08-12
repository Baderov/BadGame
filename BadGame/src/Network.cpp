#include "pch.h"
#include "Network.h"

//ip - "192.168.1.34";
//port - 2000;

void checkConnection(std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	std::wstring prefix = L"";

	packet.clear();
	prefix = L"";

	if (nm->sockNotRecv(packet, nm->getServerIP(), nm->getServerPort())) { /*DEBUG_MSG(L"recvData: sock receive error");*/ sf::sleep(sf::milliseconds(1)); return; }
	if (!(packet >> prefix)) { /*DEBUG_MSG(L"recvData: packet >> prefix error");*/ sf::sleep(sf::milliseconds(1)); return; }

	if (prefix == L"regNick")
	{
		multiplayerMenuError = MultiplayerMenuErrors::NoErrors;
		nm->setConnectsToServer(false);
	}

	else if (prefix == L"conError_nickExists")
	{
		multiplayerMenuError = MultiplayerMenuErrors::NicknameIsAlreadyTaken;
	}
}

void startNetwork(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm)
{
	while (true)
	{
		if (!nm->getConnectsToServer()) { sf::sleep(sf::milliseconds(1)); continue; }

		sf::Clock connectionClock;
		float connectionTime;

		regNickRequest(nm);
		connectionClock.restart();

		std::cout << "startNetwork" << std::endl;

		while (true)
		{
			checkConnection(nm);

			if (multiplayerMenuError == MultiplayerMenuErrors::NoErrors && !nm->getConnectsToServer())
			{
				DEBUG_MSG(L"You are connected!");
				gv->setIsMultiplayer(true);
				nm->setIsConnected(true);
				break;
			}
			else if (multiplayerMenuError == MultiplayerMenuErrors::NicknameIsAlreadyTaken)
			{
				DEBUG_MSG(L"Error: NicknameIsAlreadyTaken!");
				gv->setIsMultiplayer(false);
				nm->setConnectsToServer(false);
				break;
			}

			connectionTime = connectionClock.getElapsedTime().asSeconds();
			if (connectionTime >= 3)
			{
				multiplayerMenuError = MultiplayerMenuErrors::ServerIsNotAvailable;
				DEBUG_MSG(L"Error: ServerIsNotAvailable!");
				gv->setIsMultiplayer(false);
				nm->setConnectsToServer(false);
				break;
			}

			sf::sleep(sf::milliseconds(1));
		}
		nm->restartServerClock();
	}
}


void addConnectedClientToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& joinedNick)
{
	std::wstring joinedTheServerMsg = L" has joined the server.";
	tgui::String text = joinedNick + joinedTheServerMsg + L"\n";
	tgui::Color color = tgui::Color::Green;

	cw->addLineToChatBox(std::move(text), std::move(color));
}

void addDisconnectedClientToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& leftNick)
{
	std::wstring leftTheServerMsg = L" left the server.";
	tgui::String text = leftNick + leftTheServerMsg + L"\n";
	tgui::Color color = tgui::Color(255, 0, 0);

	cw->addLineToChatBox(std::move(text), std::move(color));
}

void addMessageToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& senderNick, std::wstring&& msg)
{
	tgui::String text = senderNick + L": " + msg + L"\n";
	tgui::Color color = tgui::Color::White;

	cw->addLineToChatBox(std::move(text), std::move(color));
}


void sendData(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw) // function to send data to the server.
{
	while (true)
	{
		if (!gv->getIsMultiplayer() || (gv->getGameState() == GameState::GameMenu) || !gv->getFocusEvent() || !nm->getIsConnected()) { sf::sleep(sf::milliseconds(1)); continue; }

		sendClientRequests(gv, gw, sm, nm, cw);
		sendBulletRequests(gv, gw, sm, nm);

		sf::sleep(sf::milliseconds(1));
	}
}

void receiveData(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw) // function to receive data from the server.
{
	sf::Packet packet;
	std::wstring prefix = L"";

	while (true)
	{
		if (!gv->getIsMultiplayer()) { sf::sleep(sf::milliseconds(1)); continue; }

		packet.clear();
		prefix = L"";

		if (gv->getIsMultiplayer() && nm->getServerClockElapsedTime() >= 5.f)
		{
			DEBUG_MSG(L"SERVER IS NOT AVAILABLE!");
			nm->setServerIsNotAvailable(true);
			nm->restartServerClock();
		}

		if (nm->sockNotRecv(packet, nm->getServerIP(), nm->getServerPort())) { /*DEBUG_MSG(L"recvData: sock receive error");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (!(packet >> prefix)) { /*DEBUG_MSG(L"recvData: packet >> prefix error");*/ sf::sleep(sf::milliseconds(1)); continue; }

		if (prefix == L"ping")
		{
			std::wstring tempNick = L"";

			if (!(packet >> tempNick)) { DEBUG_MSG(L"prefix_ping_error!"); continue; }

			nm->restartServerClock();

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != tempNick) { continue; }

				clientsVec[i]->setPing(clientsVec[i]->getPingClockElapsedTime() - clientsVec[i]->pingDelay);
				if (clientsVec[i]->getPing() < 0) { clientsVec[i]->setPing(0); }
				packet.clear();
				packet << prefix << nm->getNickname();
				nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());

				cw->changeItemInPlayersList(clientsVec[i]->getPlayersListID(), clientsVec[i]->getName(), std::to_wstring(clientsVec[i]->getPing()));

				break;
			}
		}

		else if (prefix == L"msg")
		{
			std::wstring msg = L"";
			std::wstring senderNick = L"";

			if (!(packet >> senderNick && packet >> msg)) { DEBUG_MSG(L"prefix_msg_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != senderNick) { continue; }

				nm->setAllowToSendMsg(true);

				break;
			}

			addMessageToChat(gw, nm, cw, std::move(senderNick), std::move(msg));
		}

		else if (prefix == L"mousePos")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempMousePos(0.f, 0.f);
			if (!(packet >> tempNick && packet >> tempMousePos.x && packet >> tempMousePos.y)) { DEBUG_MSG(L"prefix_mousePos_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != tempNick) { continue; }

				clientsVec[i]->rotate(gv, std::move(tempMousePos));
				clientsVec[i]->updateLaser(gv);

				break;
			}
		}

		else if (prefix == L"shoot")
		{
			std::wstring tempCreatorNick = L"";
			sf::Vector2f tempAimPos(0.f, 0.f);
			sf::Vector2f tempBulletPos(0.f, 0.f);

			if (!(packet >> tempCreatorNick && packet >> tempAimPos.x && packet >> tempAimPos.y && packet >> tempBulletPos.x && packet >> tempBulletPos.y)) { DEBUG_MSG(L"prefix_createBullet_error!"); continue; }

			std::lock_guard<std::mutex> lock(bullets_mtx);
			if (!bulletsPool.getFromPool(bulletsVec)) { break; }

			bulletsVec.back()->init(gv, std::move(tempBulletPos), std::move(tempAimPos), std::move(tempCreatorNick));
			bulletsVec.back()->setAllowToShoot(true);
		}

		else if (prefix == L"move")
		{
			std::wstring movedClientNick = L"";
			sf::Vector2f stepPos = sf::Vector2f(0.f, 0.f);

			if (!(packet >> movedClientNick && packet >> stepPos.x && packet >> stepPos.y)) { DEBUG_MSG(L"prefix_move_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != movedClientNick) { continue; }

				clientsVec[i]->setStepPos(stepPos);
				nm->setMovedClientNick(movedClientNick);
				nm->setMoveReceived(true);

				break;
			}
		}

		else if (prefix == L"ghost")
		{
			std::wstring ghostNick = L"";
			bool isGhost = false;

			if (!(packet >> ghostNick && packet >> isGhost)) { DEBUG_MSG(L"prefix_ghost_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != ghostNick) { continue; }

				clientsVec[i]->setIsGhost(isGhost);
				if (clientsVec[i]->getIsGhost()) { clientsVec[i]->setGhostSprite(); }
				else if (!clientsVec[i]->getIsGhost()) { clientsVec[i]->setRegularSprite(); }

				break;
			}
		}

		else if (prefix == L"connected")
		{
			std::wstring joinedNick = L"";
			sf::Vector2f tempPos(0.f, 0.f);
			bool isGhost = false;

			if (!(packet >> joinedNick && packet >> tempPos.x && packet >> tempPos.y && packet >> isGhost)) { DEBUG_MSG(L"prefix_connected_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			clientsPool.getFromPool(clientsVec);
			clientsVec.back()->init(gv, nm, tempPos, joinedNick);

			if (clientsVec.back()->getName() == nm->getNickname())
			{
				clientsVec.back()->setIconFillColor(sf::Color::Green);
				clientsVec.back()->getCollisionRect().setFillColor(sf::Color::Green);
				gw->setGameViewCenter(clientsVec.back()->getSpritePos());
			}
			else
			{
				clientsVec.back()->setIconFillColor(sf::Color::Magenta);
			}

			clientsVec.back()->setIsGhost(isGhost);
			clientsVec.back()->setIconPosition(clientsVec.back()->getSpritePos());
			clientsVec.back()->setPlayersListID(cw->addClientToPlayersList(joinedNick));

			addConnectedClientToChat(gw, nm, cw, std::move(joinedNick));
		}

		else if (prefix == L"disconnected")
		{
			std::wstring leftNick = L"";

			if (!(packet >> leftNick)) { DEBUG_MSG(L"prefix_disconnected_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != leftNick) { continue; }

				cw->removeClientFromPlayersList(clientsVec[i]->getPlayersListID());
				clientsPool.returnToPool(clientsVec, clientsVec[i]);

				break;
			}

			addDisconnectedClientToChat(gw, nm, cw, std::move(leftNick));
		}
	}
}


void setMoveTarget(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	std::lock_guard<std::mutex> lock(clients_mtx);
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		if (clientsVec[i]->getName() != nm->getNickname()) { continue; }
		if (!cw->editBoxIsReadOnly()) { break; }

		clientsVec[i]->setMoveTargetPos(gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)));
		clientsVec[i]->setIsMove(true);
		nm->setClientMoved(true);

		gv->playerDestination.setPosition(clientsVec[i]->getMoveTargetPos()); // set the label position to the mouse click location.
		gv->playerDestination.setOutlineColor(sf::Color::Yellow);

		break;
	}
}

void updateClients(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, Minimap& minimap)
{
	std::lock_guard<std::mutex> lock(clients_mtx);
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		clientsVec[i]->update(gv, gw, sm, nm);
	}
}

void updateBullets(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	std::lock_guard<std::mutex> lock(bullets_mtx);
	for (size_t i = 0; i < bulletsVec.size(); ++i)
	{
		bulletsVec[i]->update(gv, gw, sm, nm);
	}
}


void drawClients(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	std::lock_guard<std::mutex> lock(clients_mtx);
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		clientsVec[i]->draw(gv, gw, sm, nm);
	}
}

void drawBullets(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	std::lock_guard<std::mutex> lock(bullets_mtx);
	for (size_t i = 0; i < bulletsVec.size(); ++i)
	{
		bulletsVec[i]->draw(gv, gw, sm, nm);
	}
}

void drawWalls(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	std::lock_guard<std::mutex> lock(walls_mtx);
	for (size_t i = 0; i < wallsVec.size(); ++i)
	{
		wallsVec[i]->draw(gv, gw, sm, nm);
	}
}


void multiplayerGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	multiplayerGameUpdate(gv, gw, nm, cw);
	connectedToServerRequest(nm);

	DEBUG_MSG(L"Your nickname is " + nm->getNickname());

	while (gv->getIsMultiplayer())
	{
		DEBUG_SET_FUNC_NAME;
		updateGame(gv, gw, sm, nm, cw, minimap);
		drawGame(gv, gw, sm, nm, cw, minimap);
		updateFPS(gv);
	}
}