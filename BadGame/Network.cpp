#include "pch.h"
#include "Network.h" // header file for working with the network.

const int BACKSPACE_CODE = 8;
const int TABULATION_CODE = 9;
const int QUESTION_MARK_CODE = 63;
const int DOUBLE_QUOTES_CODE = 34;
const int SINGLE_QUOTES_CODE = 39;
const int BACKSLASH_CODE = 92;
const int ESCAPE_CODE = 27;
const int ENTER_CODE = 13;
const int CHAT_MAX_CHAR_NUM = 202;

//ip - "192.168.1.34";
//port - 2000;

int bulletID = 0;

void startNetwork(std::unique_ptr<GameVariable>& gv) // function to start network.
{
	while (true)
	{
		if (!gv->getConnectsToServer()) { sf::sleep(sf::milliseconds(1)); continue; }

		sf::Clock connectionClock;
		float connectionTime;
		connectToServerRequest(gv);
		connectionClock.restart();

		while (true)
		{
			if (multiplayerError == MultiplayerErrors::NoErrors && !gv->getConnectsToServer())
			{
				DEBUG_MSG("You are connected!");
				gv->setIsMultiplayer(true);
				break;
			}
			else if (multiplayerError == MultiplayerErrors::NicknameIsAlreadyTaken)
			{
				DEBUG_MSG("Error: NicknameIsAlreadyTaken!");
				gv->setIsMultiplayer(false);
				break;
			}
			connectionTime = connectionClock.getElapsedTime().asSeconds();
			if (connectionTime >= 3)
			{
				multiplayerError = MultiplayerErrors::ServerIsNotAvailable;
				DEBUG_MSG("Error: ServerIsNotAvailable!");
				gv->setIsMultiplayer(false);
				break;
			}

			sf::sleep(sf::milliseconds(1));
		}
		gv->serverClock.restart();
		gv->setConnectsToServer(false);
	}
}


void sendData(std::unique_ptr<GameVariable>& gv, Chat& chat) // function to send data to the server.
{
	while (true)
	{
		if (!gv->getIsMultiplayer()) { sf::sleep(sf::milliseconds(1)); continue; }
		if (gv->getInMenu()) { /*DEBUG_MSG("sendData: inMenu == true!"); */ sf::sleep(sf::milliseconds(1)); continue; }
		if (!gv->getFocusEvent()) { /*DEBUG_MSG("sendData: gv->getFocusEvent() == false!");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (!gv->getIsConnected()) { sf::sleep(sf::milliseconds(1)); continue; }

		sendClientRequests(gv, chat);
		sendBulletRequests(gv);

		sf::sleep(sf::milliseconds(1));
	}
}
void receiveData(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // function to receive data from the server.
{
	sf::IpAddress serverIP = gv->getServerIP();
	unsigned short serverPort = gv->getServerPort();
	while (true)
	{
		if (!gv->getIsMultiplayer()) { sf::sleep(sf::milliseconds(1)); continue; }

		sf::Packet packet;
		packet.clear();
		std::wstring prefix = L"";

		if (gv->serverClock.getElapsedTime().asSeconds() >= 5.f)
		{
			DEBUG_MSG("SERVER IS NOT AVAILABLE!");
			gv->setServerIsNotAvailable(true);
		}

		if (gv->sock.receive(packet, serverIP, serverPort) != sf::Socket::Done) { /*DEBUG_MSG("recvData: sock receive error");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (!(packet >> prefix)) { /*DEBUG_MSG("recvData: packet >> prefix error");*/ sf::sleep(sf::milliseconds(1)); continue; }

		if (prefix == L"ping")
		{
			std::wstring tempNick = L"";
			if (!(packet >> tempNick)) { DEBUG_MSG("prefix_ping_error!"); continue; }

			gv->serverClock.restart();

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == tempNick)
				{
					client->setPing(client->getPingClockElapsedTime() - client->pingDelay);
					if (client->getPing() < 0) { client->setPing(0); }
					packet.clear();
					packet << prefix << gv->getNickname();
					gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
					break;
				}
			}
		}

		else if (prefix == L"msg")
		{
			chat.setSenderNickname(L"");
			chat.setChatStr(L"");
			chat.setNumOfLinesInChat(1);
			std::wstring tempChatStr = L"";
			std::wstring tempSenderNickname = L"";
			int tempNumOfLinesInChat = 0;

			if (!(packet >> tempSenderNickname && packet >> tempChatStr && packet >> tempNumOfLinesInChat)) { DEBUG_MSG("prefix_msg_error!"); continue; }

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == gv->getNickname())
				{
					client->setAllowToSendMsg(true);
					break;
				}
			}

			chat.setSenderNickname(std::move(tempSenderNickname));
			chat.setChatStr(std::move(tempChatStr));
			chat.setNumOfLinesInChat(std::move(tempNumOfLinesInChat));
			chat.setRecvMsg(true);
		}

		else if (prefix == L"mousePos")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempMousePos(0.f, 0.f);
			if (!(packet >> tempNick && packet >> tempMousePos.x && packet >> tempMousePos.y)) { DEBUG_MSG("prefix_mousePos_error!"); continue; }

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == tempNick)
				{
					client->rotate(gv, std::move(tempMousePos));
					client->updateLaser(gv);
					client->setAllowToSendMousePos(true);
					break;
				}
			}
		}

		else if (prefix == L"createBullet")
		{
			std::wstring tempBulletNick = L"";
			std::wstring tempCreatorNick = L"";
			sf::Vector2f tempAimPos(0.f, 0.f);
			sf::Vector2f tempBulletPos(0.f, 0.f);
			if (!(packet >> tempBulletNick && packet >> tempCreatorNick && packet >> tempAimPos.x && packet >> tempAimPos.y && packet >> tempBulletPos.x && packet >> tempBulletPos.y)) { DEBUG_MSG("prefix_createBullet_error!"); continue; }

			std::lock_guard<std::mutex> lock(bullet_mtx);
			if (tempCreatorNick != gv->getNickname())
			{
				if (bulletPool.getFromPool(bulletVec)) { bulletVec.back()->init(gv, std::move(tempBulletPos), std::move(tempAimPos), std::move(tempBulletNick), std::move(tempCreatorNick)); }
			}
		}

		else if (prefix == L"shoot")
		{
			std::wstring tempBulletNick = L"";
			sf::Vector2f tempBulletPos(0.f, 0.f);
			if (!(packet >> tempBulletNick && packet >> tempBulletPos.x && packet >> tempBulletPos.y)) { DEBUG_MSG("prefix_mousePos_error!"); continue; }

			std::lock_guard<std::mutex> lock(bullet_mtx);
			for (auto& bullet : bulletVec)
			{
				if (bullet == nullptr) { continue; }
				if (bullet->getName() == tempBulletNick)
				{
					bullet->setSpritePos(std::move(tempBulletPos));
					bullet->setAllowToShoot(true);
					break;
				}
			}
		}

		else if (prefix == L"move")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempStepPos = sf::Vector2f(0.f, 0.f);
			if (!(packet >> tempNick && packet >> tempStepPos.x && packet >> tempStepPos.y)) { DEBUG_MSG("prefix_move_error!"); continue; }

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == tempNick)
				{
					client->moveClient(std::move(tempStepPos));
					client->setNickPosition();
					client->setAllowToMove(true);

					if (client->getName() == gv->getNickname())
					{
						gv->setGameViewCenter(client->getSpritePos());
						chat.update(gv);
						playersList.update(gv);
						minimap.update(gv);
					}

					break;
				}
			}
		}
		else if (prefix == L"collision")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempPos(0.f, 0.f);
			if (!(packet >> tempNick && packet >> tempPos.x && packet >> tempPos.y)) { DEBUG_MSG("prefix_collision_error!"); continue; }

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == tempNick)
				{
					client->setClientPosition(std::move(tempPos));
					client->setNickPosition();
					client->setAllowToCollision(true);
					client->setIsCollision(false);
					//gv->setGameViewCenter(client->getSpritePos());
					//std::cout << "recv: collision, client posX : " << client->getSpritePos().x << " posY : " << client->getSpritePos().y << "\n";
					break;
				}
			}
		}

		else if (prefix == L"connected")
		{
			std::wstring tempJoinedMsg = L"", tempJoinedNick = L"";
			sf::Vector2f tempPos(0.f, 0.f);
			chat.setJoinedNick(L"");
			chat.setJoinedMsg(L"");
			if (!(packet >> tempJoinedNick && packet >> tempPos.x && packet >> tempPos.y && packet >> tempJoinedMsg)) { DEBUG_MSG("prefix_connected_error!"); continue; }

			chat.setJoinedNick(tempJoinedNick);
			chat.setJoinedMsg(chat.getJoinedNick() + tempJoinedMsg);
			chat.setJoinToServer(true);

			std::lock_guard<std::mutex> lock(client_mtx);
			clientPool.getFromPool(clientVec);
			clientVec.back()->init(gv, tempPos, tempJoinedNick);

			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == gv->getNickname()) { gv->setGameViewCenter(client->getSpritePos()); client->setIconFillColor(sf::Color::Green); gv->setIsConnected(true); }
				else { client->setIconFillColor(sf::Color::Magenta); }
				client->setIconPosition(client->getSpritePos());
			}

			playersList.updateScrollbar();
		}
		else if (prefix == L"disconnected")
		{
			std::wstring tempLeftMsg = L"", tempLeftNick = L"";
			chat.setLeftNick(L"");
			chat.setLeftMsg(L"");
			if (!(packet >> tempLeftNick && packet >> tempLeftMsg)) { DEBUG_MSG("prefix_disconnected_error!"); continue; }

			chat.setLeftNick(tempLeftNick);
			chat.setLeftMsg(chat.getLeftNick() + tempLeftMsg);

			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == tempLeftNick) { clientPool.returnToPool(clientVec, client); }
			}
			clientPool.eraseEmptyVecElements(clientVec);

			playersList.updateScrollbar();
			if (tempLeftNick != gv->getNickname())
			{
				chat.setChatStr(chat.getLeftMsg());
				chat.setLeftFromServer(true);
			}
		}
		else if (prefix == L"conError_nickExists")
		{
			multiplayerError = MultiplayerErrors::NicknameIsAlreadyTaken;
			gv->setIsMultiplayer(false);
			gv->setConnectsToServer(false);
		}
		else if (prefix == L"regNick")
		{
			DEBUG_MSG("REGNICK");
			multiplayerError = MultiplayerErrors::NoErrors;
			gv->setIsMultiplayer(true);
			gv->setConnectsToServer(false);
		}
	}
}


void updateClients(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> lock(client_mtx);
	for (auto& client : clientVec)
	{
		if (client == nullptr) { continue; }

		for (auto& client2 : clientVec)
		{
			if (client2 == nullptr) { continue; }
			collisionHandler(gv, client.get(), client2.get());
		}

		for (auto& wall : wallVec)
		{
			if (wall == nullptr) { continue; }
			collisionHandler(gv, client.get(), wall.get());
		}

		client->update(gv);
		if (client->getName() == gv->getNickname())
		{
			gv->setGameViewCenter(client->getSpritePos());
			chat.update(gv);
			playersList.update(gv);
			minimap.update(gv);
		}
	}
}

void updateBullets(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> lock(bullet_mtx);
	for (auto& bullet : bulletVec)
	{
		if (bullet == nullptr) { continue; }
		bullet->update(gv);
		if (!bullet->getIsAlive()) { bulletPool.returnToPool(bulletVec, bullet); }
	}
	bulletPool.eraseEmptyVecElements(bulletVec);
}

void gameUpdate(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	if (!gv->getIsConnected()) { return; }

	gv->setMenuNum(0);
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
	gv->setDT();

	while (gv->window.pollEvent(gv->event)) { m_eventHandler(gv, minimap, playersList, chat); }

	updateServerIsNotAvailable(gv, chat);
	updateClients(gv, minimap, playersList, chat);
	updateBullets(gv, minimap, playersList, chat);
}


void drawClients(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat, bool&& isMinimapView)
{
	//	std::lock_guard<std::mutex> lock(client_mtx);
	for (auto& client : clientVec)
	{
		if (client == nullptr) { continue; }
		if (isMinimapView) { client->drawIcon(gv); }
		else
		{
			client->drawNameText(gv);
			client->drawSprite(gv);
			if (client->getName() == gv->getNickname() && client->getIsMove() && !gv->getServerIsNotAvailable()) { gv->window.draw(gv->playerDestination); }
		}
	}
}

void drawBullets(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> lock(bullet_mtx);
	for (auto& bullet : bulletVec)
	{
		if (bullet == nullptr) { continue; }
		bullet->drawSprite(gv);
	}
}

void drawWalls(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> lock(wall_mtx);
	for (auto& wall : wallVec)
	{
		if (wall == nullptr) { continue; }
		wall->drawSprite(gv);
	}
}





void minimapViewDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	if (gv->getShowMinimap())
	{
		std::lock_guard<std::mutex> lock(client_mtx);
		minimap.setView(gv);

		drawWalls(gv, minimap, playersList, chat);
		drawClients(gv, minimap, playersList, chat, true);

		gv->setGameView();
	}
}

void gameViewDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> lock(client_mtx);
	gv->setGameView();

	drawWalls(gv, minimap, playersList, chat);
	drawBullets(gv, minimap, playersList, chat);
	drawClients(gv, minimap, playersList, chat, false);

	if (gv->getShowAimLaser() && gv->getFocusEvent()) { gv->window.draw(gv->aimLaser); }
	chat.draw(gv);
	playersList.draw(gv);
	minimap.draw(gv);
	drawServerIsNotAvailable(gv);
}

void gameDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	if (!gv->getIsMultiplayer() || !gv->getIsConnected()) { return; }

	gv->window.clear(gv->backgroundColor);

	gameViewDraw(gv, minimap, playersList, chat);
	minimapViewDraw(gv, minimap, playersList, chat);

	gv->window.display();
}


void m_eventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // event handler for multiplayer.
{
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->setIsMultiplayer(false);
		gv->window.close();
		break;
	case sf::Event::LostFocus:
		playersList.setShowPlayersList(false);
		gv->setFocusEvent(false);
		break;
	case sf::Event::GainedFocus:
		gv->setFocusEvent(true);
		break;
	case sf::Event::MouseButtonPressed:
		switch (gv->event.mouseButton.button) // check by mouse button.
		{
		case sf::Mouse::Left:

			if (gv->getMenuNum() == 0)
			{
				chat.setChatContainsMouse(false);
				chat.setTextInputMode(false);
				chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));

				std::lock_guard<std::mutex> lock(client_mtx);
				for (auto& client : clientVec)
				{
					if (client == nullptr) { continue; }
					if (client->getName() == gv->getNickname())
					{
						client->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)));
						client->setIsMove(true);
						gv->playerDestination.setPosition(client->getMoveTargetPos()); // set the label position to the mouse click location.
						gv->playerDestination.setOutlineColor(sf::Color::Yellow);
						break;
					}
				}
			}

			if (gv->getMenuNum() == 1)
			{
				chat.setChatContainsMouse(true);
				chat.setTextInputMode(true);
				chat.getUserTextBox().setFillColor(sf::Color::White);

				std::lock_guard<std::mutex> lock(client_mtx);
				for (auto& client : clientVec)
				{
					if (client == nullptr) { continue; }
					if (client->getName() == gv->getNickname())
					{
						client->setIsMove(false);
						break;
					}
				}
			}

			else if (gv->getMenuNum() == 2)
			{
				chat.setChatContainsMouse(true);
				chat.setTextInputMode(false);
				chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));

				std::lock_guard<std::mutex> lock(client_mtx);
				for (auto& client : clientVec)
				{
					if (client == nullptr) { continue; }
					if (client->getName() == gv->getNickname())
					{
						client->setIsMove(false);
						break;
					}
				}
			}

			else if (gv->getMenuNum() == 3)
			{
				playersList.setShowPlayersList(false);
				gv->setIsMultiplayer(false);
				gv->setMenuNum(0);
				return;
			}
			break;
		case sf::Mouse::Right:
			std::lock_guard<std::mutex> lock(client_mtx);
			for (auto& client : clientVec)
			{
				if (client == nullptr) { continue; }
				if (client->getName() == gv->getNickname() && !client->getIsShoot() && bulletPool.getFromPool(bulletVec) && !gv->getServerIsNotAvailable())
				{
					client->setIsShoot(true);
					bulletID++;
					bulletVec.back()->init(gv, client->getSpritePos(), gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)), L"Bullet" + std::to_wstring(bulletID), client->getName());
					createBulletRequest(gv, bulletVec.back()->getName(), bulletVec.back()->getCreatorName(), bulletVec.back()->getAimPos(), bulletVec.back()->getSpritePos());
					client->setCurrentAmmo(client->getCurrentAmmo() - 1);
					client->setIsShoot(false);
					break;
				}
			}
			break;
		}
		break;
	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // check by key code.
		{
			//case sf::Keyboard::P:
			//	if (!chat.getChatEnterText()) { gv->setChatAutoScroll(!(gv->getChatAutoScroll())); }
			//	break;
		case sf::Keyboard::Tab:
			if (!playersList.getShowPlayersList() && !gv->getServerIsNotAvailable()) { playersList.setShowPlayersList(true); }
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::C:
			if (!chat.getTextInputMode() && !gv->getServerIsNotAvailable()) { gv->setShowAimLaser(!(gv->getShowAimLaser())); }
			break;
		case sf::Keyboard::Tab:
			if (playersList.getShowPlayersList()) { playersList.setShowPlayersList(false); }
			break;
		case sf::Keyboard::Escape:
			playersList.setShowPlayersList(false);
			gv->setInMenu(true);
			menuEventHandler(gv, minimap, playersList, chat);
			gv->setInMenu(false);
			gv->setGameView();
			gv->gameClock.restart();
			break;
		case sf::Keyboard::O:
			if (!chat.getTextInputMode() && !gv->getServerIsNotAvailable()) { chat.setShowChat(!(chat.getShowChat())); }
			break;
		case sf::Keyboard::M:
			if (!chat.getTextInputMode() && !gv->getServerIsNotAvailable()) { gv->setShowMinimap(!(gv->getShowMinimap())); }
			break;
		}
		break;
	case sf::Event::MouseWheelMoved:
		if (gv->event.mouseWheel.delta == 1)
		{
			if (((chat.getStrVector().size() - chat.getScrollbarStepNumber()) > 10) && chat.getStrVector().size() > 10 && chat.getChatContainsMouse() && chat.getShowChat())
			{
				chat.setScrollbarDir(L"up");
			}
			if ((clientVec.size() - playersList.getScrollbarStepNumber() > NUM_OF_DISPLAYED_PLAYERS) && playersList.getShowPlayersList() && playersList.getPLContainsMouse())
			{
				playersList.setScrollbarDir(L"up");
			}
		}
		else if (gv->event.mouseWheel.delta == -1)
		{
			if (chat.getScrollbarStepNumber() > 0 && chat.getStrVector().size() > 10 && chat.getChatContainsMouse() && chat.getShowChat())
			{
				chat.setScrollbarDir(L"down");
			}
			if (playersList.getScrollbarStepNumber() > 0 && playersList.getShowPlayersList() && playersList.getPLContainsMouse())
			{
				playersList.setScrollbarDir(L"down");
			}
		}
		break;
	case sf::Event::TextEntered:
		if (chat.getTextInputMode() && chat.getShowChat())
		{
			if (gv->event.text.unicode == BACKSPACE_CODE)
			{
				if (chat.getUserStr().size() > 0)
				{
					std::wstring tempStr = chat.getUserStr();
					tempStr.resize(chat.getUserStr().size() - 1);
					chat.setUserStr(tempStr);
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
					if (!chat.getUserStr().empty())
					{
						if (chat.getUserStr()[chat.getUserStr().size() - 1] == '\n')
						{
							tempStr = chat.getUserStr();
							tempStr.resize(chat.getUserStr().size() - 1);
							chat.setUserStr(tempStr);
							chat.setNumOfLinesInUserTextBox(chat.getNumOfLinesInUserTextBox() - 1);
						}
					}
				}
			}
			else if (gv->event.text.unicode == ENTER_CODE)
			{
				if (chat.getUserStr().size() > 0 && chat.getUserStr().size() <= CHAT_MAX_CHAR_NUM && !chat.getSendMsg() && !chat.getRecvMsg())
				{
					std::wstring tempUserStr = chat.getUserStr();
					if (chat.trimString(tempUserStr)) { chat.setSendMsg(true); }
					else
					{
						chat.setNumOfLinesInUserTextBox(1);
						chat.getUserText().clear();
						chat.setUserStr(L"");
					}
				}
			}
			else if (gv->event.text.unicode == QUESTION_MARK_CODE)
			{
				if (chat.getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine();
					chat.setUserStr(chat.getUserStr() + L"\?");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
				}
			}
			else if (gv->event.text.unicode == DOUBLE_QUOTES_CODE)
			{
				if (chat.getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine();
					chat.setUserStr(chat.getUserStr() + L"\"");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
				}
			}
			else if (gv->event.text.unicode == SINGLE_QUOTES_CODE)
			{
				if (chat.getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine();
					chat.setUserStr(chat.getUserStr() + L"\'");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
				}
			}
			else if (gv->event.text.unicode == BACKSLASH_CODE)
			{
				if (chat.getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine();
					chat.setUserStr(chat.getUserStr() + L"\\");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
				}
			}
			else if (gv->event.text.unicode != BACKSPACE_CODE && gv->event.text.unicode != ESCAPE_CODE && gv->event.text.unicode != TABULATION_CODE)
			{
				if (chat.getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine();
					std::wstring tempStr = chat.getUserStr();
					tempStr += gv->event.text.unicode;
					chat.setUserStr(tempStr);
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << chat.getUserStr();
				}
			}
		}
		break;
	}
}
void multiplayerGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // multiplayer game launch function.
{
	while (gv->getIsMultiplayer())
	{
		DEBUG_SET_FUNC_NAME;
		gameUpdate(gv, minimap, playersList, chat);
		gameDraw(gv, minimap, playersList, chat);
	}
}