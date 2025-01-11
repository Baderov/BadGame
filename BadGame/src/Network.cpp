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
	sf::Clock connectionClock;
	float connectionTime;

	regNickRequest(nm);
	connectionClock.restart();

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
		if (!gv->getIsMultiplayer() || gv->getGameState() == GameState::GameMenu || !gv->getFocusEvent() || !nm->getIsConnected()) { sf::sleep(sf::milliseconds(1)); continue; }

		sendClientRequests(gv, gw, sm, nm, cw);

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

		if (nm->getServerClockElapsedTime() >= 5.f)
		{
			DEBUG_MSG(L"SERVER IS NOT AVAILABLE!");
			nm->setServerIsNotAvailable(true);
			nm->restartServerClock();
		}

		if (nm->sockNotRecv(packet, nm->getServerIP(), nm->getServerPort())) { /*DEBUG_MSG(L"recvData: sock receive error");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (!(packet >> prefix)) { /*DEBUG_MSG(L"recvData: packet >> prefix error");*/ sf::sleep(sf::milliseconds(1)); continue; }

		if (prefix == L"ping")
		{
			std::wstring clientNick = L"";

			if (!(packet >> clientNick)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			nm->restartServerClock();

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != clientNick) { continue; }

				clientsVec[i]->setPing(clientsVec[i]->getPingClockElapsedTime() - clientsVec[i]->pingDelay);
				if (clientsVec[i]->getPing() < 0) { clientsVec[i]->setPing(0); }
				packet.clear();
				packet << prefix << nm->getCurrentNickname();
				nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
				cw->changeItemInPlayersList(clientsVec[i]->getPlayersListID(), clientsVec[i]->getName(), std::to_wstring(clientsVec[i]->getPing()));

				break;
			}
		}

		else if (prefix == L"msg")
		{
			std::wstring clientMsg = L"";
			std::wstring clientNick = L"";

			if (!(packet >> clientNick && packet >> clientMsg)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			if (nm->getCurrentNickname() == clientNick) { nm->setMsgReceived(true); }

			addMessageToChat(gw, nm, cw, std::move(clientNick), std::move(clientMsg));
		}

		else if (prefix == L"mousePos")
		{
			std::wstring clientNick = L"";
			sf::Vector2f clientMousePos(0.f, 0.f);

			if (!(packet >> clientNick && packet >> clientMousePos.x && packet >> clientMousePos.y)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (!cw->editBoxIsReadOnly()) { break; }
				if (clientsVec[i]->getName() != clientNick) { continue; }

				clientsVec[i]->rotate(gv, std::move(clientMousePos));

				break;
			}
		}

		else if (prefix == L"shoot")
		{
			std::wstring bulletCreatorNick = L"";
			sf::Vector2f bulletAimPos(0.f, 0.f);
			sf::Vector2f bulletPos(0.f, 0.f);
			sf::Vector2f currentVelocity(0.f, 0.f);

			if (!(packet >> bulletCreatorNick && packet >> bulletAimPos.x && packet >> bulletAimPos.y && packet >> bulletPos.x && packet >> bulletPos.y
				&& packet >> currentVelocity.x && packet >> currentVelocity.y)) {
				DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue;
			}

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != bulletCreatorNick) { continue; }

				clientsVec[i]->createBullet(gv, gw, sm, nm, std::move(bulletPos), std::move(bulletAimPos), std::move(bulletCreatorNick), std::move(currentVelocity));

				break;
			}
		}

		else if (prefix == L"move")
		{
			std::wstring clientNick = L"";
			sf::Vector2f clientNewPos(0.f, 0.f);

			if (!(packet >> clientNick && packet >> clientNewPos.x && packet >> clientNewPos.y)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != clientNick) { continue; }

				clientsVec[i]->setNewPos(std::move(clientNewPos));
				clientsVec[i]->setMoveReceived(true);

				break;
			}
		}

		else if (prefix == L"hit")
		{
			std::wstring shooterClientNick = L"";
			std::wstring woundedClientNick = L"";
			int woundedClientHP = 0;
			bool woundedClientDead = false;

			if (!(packet >> shooterClientNick && packet >> woundedClientNick && packet >> woundedClientHP && packet >> woundedClientDead)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != woundedClientNick) { continue; }

				clientsVec[i]->setHP(clientsVec[i]->getHP() - 10);

				break;
			}

			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != shooterClientNick) { continue; }

				if (woundedClientDead)
				{
					clientsVec[i]->setNumOfKills(clientsVec[i]->getNumOfKills() + 1);

				}

				break;
			}
		}

		else if (prefix == L"ghost")
		{
			std::wstring clientNick = L"";
			bool isGhost = false;

			if (!(packet >> clientNick && packet >> isGhost)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != clientNick) { continue; }

				clientsVec[i]->setIsGhost(std::move(isGhost));
				if (clientsVec[i]->getIsGhost()) { clientsVec[i]->setGhostSprite(); }
				else if (!clientsVec[i]->getIsGhost()) { clientsVec[i]->setRegularSprite(nm->getCurrentNickname()); }

				break;
			}
		}

		else if (prefix == L"connected")
		{
			std::wstring clientNick = L"";
			sf::Vector2f clientPos(0.f, 0.f);
			int HP = 100;

			if (!(packet >> clientNick && packet >> clientPos.x && packet >> clientPos.y && packet >> HP)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			clientsPool.getFromPool(clientsVec);
			clientsVec.back()->init(gv, nm, clientNick, clientPos, HP);
			clientsVec.back()->checkCollision(gv, gw, sm, nm);

			if (clientsVec.back()->getName() == nm->getCurrentNickname())
			{
				if (clientsVec.back()->getIsCollision())
				{
					bool tempIsGhost = true;
					ghostRequest(nm, std::move(tempIsGhost));
				}

				clientsVec.back()->getCollider().setFillColor(sf::Color::Green);
				clientsVec.back()->setIconFillColor(sf::Color::Green);
				clientsVec.back()->setNameTextFillColor(sf::Color::Cyan);
				gw->setGameViewCenter(clientsVec.back()->getSpritePos());
			}
			else
			{
				clientsVec.back()->setIconFillColor(sf::Color::Magenta);
				clientsVec.back()->setNameTextFillColor(sf::Color::Red);
			}

			clientsVec.back()->setPlayersListID(cw->addClientToPlayersList(clientNick));

			addConnectedClientToChat(gw, nm, cw, std::move(clientNick));

		}

		else if (prefix == L"disconnected")
		{
			std::wstring clientNick = L"";

			if (!(packet >> clientNick)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != clientNick) { continue; }

				cw->removeClientFromPlayersList(clientsVec[i]->getPlayersListID());
				clientsPool.returnToPool(clientsVec, clientsVec[i]);

				break;
			}

			addDisconnectedClientToChat(gw, nm, cw, std::move(clientNick));
		}

		else if (prefix == L"respawn")
		{
			std::wstring clientNick = L"";
			sf::Vector2f clientStartPos(0.f, 0.f);
			int HP = 100;

			if (!(packet >> clientNick && packet >> clientStartPos.x && packet >> clientStartPos.y)) { DEBUG_MSG(L"prefix_" << prefix << "_error!"); continue; }

			std::lock_guard<std::mutex> lock(clients_mtx);
			for (size_t i = 0; i < clientsVec.size(); ++i)
			{
				if (clientsVec[i]->getName() != clientNick) { continue; }

				clientsVec[i]->init(gv, nm, clientNick, clientStartPos, HP);
				clientsVec[i]->checkCollision(gv, gw, sm, nm);

				if (clientsVec[i]->getName() == nm->getCurrentNickname())
				{
					if (clientsVec[i]->getIsCollision())
					{
						bool tempIsGhost = true;
						ghostRequest(nm, std::move(tempIsGhost));
					}

					clientsVec[i]->getCollider().setFillColor(sf::Color::Green);
					clientsVec[i]->setIconFillColor(sf::Color::Green);
					clientsVec[i]->setNameTextFillColor(sf::Color::Cyan);
				}
				else
				{
					clientsVec[i]->setIconFillColor(sf::Color::Magenta);
					clientsVec[i]->setNameTextFillColor(sf::Color::Red);
				}

				break;
			}
		}
	}
}


void updateClients(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
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
		if (clientsVec[i]->getName() == nm->getCurrentNickname()) { continue; }

		clientsVec[i]->draw(gv, gw, sm, nm);
	}
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		if (clientsVec[i]->getName() != nm->getCurrentNickname()) { continue; }

		clientsVec[i]->draw(gv, gw, sm, nm);

		break;
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
	while (gv->getIsMultiplayer())
	{
		updateGame(gv, gw, sm, nm, cw, minimap);
		drawGame(gv, gw, sm, nm, cw, minimap);
		updateFPS(gv);
	}
}