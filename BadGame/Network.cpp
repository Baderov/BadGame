#include "pch.h"
#include "Network.h" // header file for working with the network.

#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::wcout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

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

void createWalls(GameVariable* gv)
{
	std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
	gv->entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"LeftWall", wallSize)); // create a left wall and throw it into the list of entities.
	gv->entitiesVec.emplace_back(new Wall(sf::Vector2f(5000.f, 0.f), L"RightWall", wallSize)); // create a right wall and throw it into the list of entities.
	gv->entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"TopWall", wallSize)); // create a top wall and throw it into the list of entities.
	gv->entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 4936.f), L"BottomWall", wallSize)); // create a bottom wall and throw it into the list of entities.
}

void serverIsNotAvailable(GameVariable* gv)
{
	gv->connectionErrorRS.setSize(sf::Vector2f(1000.f, 300.f));
	gv->connectionErrorRS.setFillColor(sf::Color(0, 0, 0, 200));
	gv->connectionErrorRS.setOrigin(gv->connectionErrorRS.getSize() / 2.f);
	gv->connectionErrorRS.setPosition(getCurrentClientPos());
	gv->OKButtonRS.setSize(sf::Vector2f(130.f, 130.f));
	gv->OKButtonRS.setFillColor(sf::Color(255, 255, 255, 200));
	gv->OKButtonRS.setOrigin(gv->OKButtonRS.getSize() / 2.f);
	gv->OKButtonRS.setPosition(gv->connectionErrorRS.getPosition().x, gv->connectionErrorRS.getPosition().y + 40.f);

	gv->connectionErrorText.setFont(gv->consolasFont);
	gv->connectionErrorText.setCharacterSize(70);
	gv->connectionErrorText.setFillColor(sf::Color::Red);
	if (gv->getGameLanguage() == 'e') { gv->connectionErrorText.setString(L"SERVER IS NOT AVAILABLE!"); }
	else if (gv->getGameLanguage() == 'r') { gv->connectionErrorText.setString(L"яепбеп меднярсоем!"); }
	gv->connectionErrorText.setOrigin(round(gv->connectionErrorText.getLocalBounds().left + (gv->connectionErrorText.getLocalBounds().width / 2.f)), round(gv->connectionErrorText.getLocalBounds().top + (gv->connectionErrorText.getLocalBounds().height / 2.f)));
	gv->connectionErrorText.setPosition(gv->connectionErrorRS.getPosition().x, gv->connectionErrorRS.getPosition().y - 80.f);

	gv->OKButtonText.setFont(gv->consolasFont);
	gv->OKButtonText.setCharacterSize(70);
	gv->OKButtonText.setFillColor(sf::Color::Black);
	gv->OKButtonText.setString("OK");
	gv->OKButtonText.setOrigin(round(gv->OKButtonText.getLocalBounds().left + (gv->OKButtonText.getLocalBounds().width / 2.f)), round(gv->OKButtonText.getLocalBounds().top + (gv->OKButtonText.getLocalBounds().height / 2.f)));
	gv->OKButtonText.setPosition(gv->OKButtonRS.getPosition());
}

void m_enterMenu(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // enter menu for multiplayer.
{
	gv->setShowPlayersList(false);
	gv->setInMenu(true);

	menuEventHandler(gv, minimap, playersList, chat);

	gv->setWindowView(gv->getGameView());
	gv->gameClock.restart();
	gv->setInMenu(false);
}

void connectToServer(GameVariable* gv) // function to connect to the server.
{
	std::wstring prefix = L"regNick";
	sf::Packet packet;
	packet << prefix << gv->getNickname();
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void startNetwork(GameVariable* gv) // function to start network.
{
	gv->setConnectsToServer(true);
	sf::Clock connectionClock;
	float connectionTime;
	connectToServer(gv);
	connectionClock.restart();
	while (gv->window.isOpen())
	{
		if (gv->multiplayerError == MultiplayerErrors::NoErrors && gv->getConnectsToServer() == false)
		{
			DEBUG_MSG("You are connected!");
			gv->setIsConnected(true);
			break;
		}
		else if (gv->multiplayerError == MultiplayerErrors::NicknameIsAlreadyTaken)
		{
			DEBUG_MSG("Error: NicknameIsAlreadyTaken!");
			gv->setIsMultiplayer(false);
			gv->setIsConnected(false);
			break;
		}
		connectionTime = connectionClock.getElapsedTime().asSeconds();
		if (connectionTime >= 3)
		{
			gv->multiplayerError = MultiplayerErrors::ServerIsNotAvailable;
			DEBUG_MSG("Error: ServerIsNotAvailable!");
			gv->setIsMultiplayer(false);
			gv->setIsConnected(false);
			break;
		}
		sf::sleep(sf::milliseconds(1));
	}
	gv->setConnectsToServer(false);
}

bool checkConnection(GameVariable* gv)
{
	if (gv->getIsMultiplayer() == false)
	{
		clearEntitiesVec(gv);
		DEBUG_MSG("You are disconnected!");
		return false;
	}
	else { return true; }
}

void sendMessage(GameVariable* gv, Chat& chat) // function to send message to the server.
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"msg";
	packet << prefix << gv->getNickname() << chat.getUserStr() << chat.getNumOfLinesInUserTextBox();
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void sendMoveRequest(GameVariable* gv) // sending a move request to the server
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"move";
	packet << prefix << gv->getNickname() << getCurrentClientStepPos().x << getCurrentClientStepPos().y;
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void sendMousePos(GameVariable* gv)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"mousePos";
	packet << prefix << gv->getNickname() << gv->getMousePos().x << gv->getMousePos().y;
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void m_eventHandler(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // event handler for multiplayer.
{
	if (currentClientIsNullptr() == true) { return; }
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->setIsMultiplayer(false);
		clearEntitiesVec(gv);
		gv->window.close();
		break;
	case sf::Event::LostFocus:
		gv->setShowPlayersList(false);
		gv->setFocusEvent(false);
		break;
	case sf::Event::GainedFocus:
		gv->setFocusEvent(true);
		break;
	case sf::Event::MouseButtonPressed:
		switch (gv->event.mouseButton.button) // check by mouse button.
		{
		case sf::Mouse::Left:
			if (gv->getServerIsNotAvailable() == true && gv->getMenuNum() == 3)
			{
				gv->setShowPlayersList(false);
				gv->setInMenu(true);
				gv->setIsMultiplayer(false);
				gv->setMenuNum(0);
				return;
			}
			if (gv->getMenuNum() == 0 && gv->getServerIsNotAvailable() == false)
			{
				chat.setChatEnterText(false);
				chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
			}
			else if (gv->getMenuNum() == 1 && gv->getServerIsNotAvailable() == false)
			{
				chat.setChatEnterText(true);
				setCurrentClientIsMove(false);
				chat.getUserTextBox().setFillColor(sf::Color::White);
			}
			if (chat.getChatEnterText() == false)
			{
				setCurrentClientMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
				setCurrentClientIsMove(true);
				gv->playerDestination.setPosition(getCurrentClientMoveTargetPos()); // set the label position to the mouse click location.
				gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			}
			break;
		case sf::Mouse::Right:
			setCurrentClientIsShoot(true);
			break;
		}
		break;
	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // check by key code.
		{
			//case sf::Keyboard::P:
			//	if (chat.getChatEnterText() == false) { gv->setChatAutoScroll(!(gv->getChatAutoScroll())); }
			//	break;
		case sf::Keyboard::Tab:
			if (gv->getShowPlayersList() == false && gv->getServerIsNotAvailable() == false) { gv->setShowPlayersList(true); }
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::C:
			if (chat.getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { gv->setShowAimLaser(!(gv->getShowAimLaser())); }
			break;
		case sf::Keyboard::Tab:
			if (gv->getShowPlayersList() == true) { gv->setShowPlayersList(false); }
			break;
		case sf::Keyboard::Escape:
			m_enterMenu(gv, minimap, playersList, chat);
			break;
		case sf::Keyboard::O:
			if (chat.getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { chat.setShowChat(!(chat.getShowChat())); }
			break;
		case sf::Keyboard::M:
			if (chat.getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { gv->setShowMinimap(!(gv->getShowMinimap())); }
			break;
		}
		break;
	case sf::Event::MouseWheelMoved:
		if (gv->event.mouseWheel.delta == 1)
		{
			if (((chat.getStrVector().size() - chat.getScrollbarStepNumber()) > 10) && chat.getStrVector().size() > 10 && chat.getChatContainsMouse() == true && chat.getShowChat() == true)
			{
				chat.setScrollbarDir(L"up");
			}
			if ((Entity::getNumOfClients() - playersList.getScrollbarStepNumber() > NUM_OF_DISPLAYED_PLAYERS) && gv->getShowPlayersList() == true)
			{
				playersList.setScrollbarDir(L"up");
			}
		}
		else if (gv->event.mouseWheel.delta == -1)
		{
			if (chat.getScrollbarStepNumber() > 0 && chat.getStrVector().size() > 10 && chat.getChatContainsMouse() == true && chat.getShowChat() == true)
			{
				chat.setScrollbarDir(L"down");
			}
			if (playersList.getScrollbarStepNumber() > 0 && gv->getShowPlayersList() == true)
			{
				playersList.setScrollbarDir(L"down");
			}
		}
		break;
	case sf::Event::TextEntered:
		if (chat.getChatEnterText() == true && chat.getShowChat() == true)
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
				if (chat.getUserStr().size() > 0 && chat.getUserStr().size() <= CHAT_MAX_CHAR_NUM && chat.getSendMsg() == false && chat.getRecvMsg() == false)
				{
					std::wstring tempUserStr = chat.getUserStr();
					if (chat.trimString(tempUserStr) == true)
					{
						chat.setSendMsg(true);
					}
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

void sendData(GameVariable* gv, Chat& chat) // function to send data to the server.
{
	DEBUG_MSG("SEND DATA START");
	while (gv->getIsMultiplayer() == true)
	{
		if (gv->getInMenu() == true) { /*DEBUG_MSG("sendData: gv->getInMenu() == true");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (gv->getFocusEvent() == false) {/* DEBUG_MSG("sendData: gv->getFocusEvent() == false");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if (currentClientIsNullptr() == true) { /*DEBUG_MSG("sendData: clientIsNullptr() == true");*/ sf::sleep(sf::milliseconds(1)); continue; }

		if (gv->getIsConnected() == true)
		{
			sendMousePos(gv);
			if (chat.getSendMsg() == true)
			{
				chat.setSendMsg(false);
				sendMessage(gv, chat);
			}
			if (getCurrentClientIsMove() == true)
			{
				callMoveToTarget(gv->getDT(), gv->getIsSingleplayer());
				sendMoveRequest(gv);
			}
		}

		sf::sleep(sf::milliseconds(1));
	}
	DEBUG_MSG("SEND DATA END");
}

void receiveData(GameVariable* gv, PlayersList& playersList, Chat& chat) // function to receive data from the server.
{
	DEBUG_MSG("RECV DATA START");
	sf::IpAddress serverIP = gv->getServerIP();
	unsigned short serverPort = gv->getServerPort();
	while (gv->getIsMultiplayer() == true)
	{
		sf::Packet packet;
		packet.clear();
		std::wstring prefix = L"";

		gv->setServerTime(gv->getServerClockElapsedTime());
		if (gv->getServerTime() >= 5.f)
		{
			DEBUG_MSG("SERVER IS NOT AVAILABLE!");
			gv->setServerIsNotAvailable(true);
		}

		if (gv->sock.receive(packet, serverIP, serverPort) != sf::Socket::Done) { /*DEBUG_MSG("recvData: sock receive error");*/ sf::sleep(sf::milliseconds(1)); continue; }
		if ((!(packet >> prefix))) { /*DEBUG_MSG("recvData: packet >> prefix error");*/ sf::sleep(sf::milliseconds(1)); continue; }

		if (prefix == L"ping")
		{
			std::wstring tempNick = L"";
			if (!(packet >> tempNick)) { DEBUG_MSG("prefix_ping_error!"); continue; }

			gv->restartServerClock();

			std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
			for (auto& entity : gv->entitiesVec)
			{
				if (entity->getEntityType() == "Client" && tempNick == entity->getName())
				{
					entity->setPing(entity->getPingClock().restart().asMilliseconds() - gv->getPingDelay());
					if (entity->getPing() < 0) { entity->setPing(0); }

					packet.clear();
					packet << prefix << gv->getNickname();
					gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
					break;
				}
			}
		}
		else if (prefix == L"conError_nickExists")
		{
			gv->multiplayerError = MultiplayerErrors::NicknameIsAlreadyTaken;
			gv->setIsMultiplayer(false);
			gv->setConnectsToServer(false);
		}
		else if (prefix == L"regNick")
		{
			gv->multiplayerError = MultiplayerErrors::NoErrors;
			gv->setIsMultiplayer(true);
			gv->setConnectsToServer(false);
		}
		else if (prefix == L"mousePos")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempMousePos;
			if (!(packet >> tempNick && packet >> tempMousePos.x && packet >> tempMousePos.y)) { DEBUG_MSG("prefix_clientUpdate_error!"); continue; }

			std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
			for (auto& entity : gv->entitiesVec)
			{
				if (entity->getEntityType() == "Client" && entity->getName() == tempNick)
				{
					entity->rotate(gv->aimLaser, tempMousePos);
					break;
				}
			}
		}
		else if (prefix == L"move")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempStepPos = sf::Vector2f(0.f, 0.f);
			if (!(packet >> tempNick && packet >> tempStepPos.x && packet >> tempStepPos.y)) { DEBUG_MSG("prefix_move_error!"); continue; }

			std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
			for (auto& entity : gv->entitiesVec)
			{
				if (entity->getEntityType() == "Client" && entity->getName() == tempNick)
				{
					entity->setClientPosition(tempStepPos);
					entity->setNickPosition();
					break;
				}
			}
		}
		else if (prefix == L"connected")
		{
			std::wstring tempJoinedMsg = L"", tempJoinedNick = L"";
			sf::Vector2f tempPos = sf::Vector2f(0.f, 0.f);
			int currentClientID = 0;
			int tempID = 0;
			chat.setJoinedNick(L"");
			chat.setJoinedMsg(L"");
			if (!(packet >> tempJoinedNick && packet >> tempPos.x && packet >> tempPos.y && packet >> tempJoinedMsg)) { DEBUG_MSG("prefix_connected_error!"); continue; }

			chat.setJoinedNick(tempJoinedNick);
			chat.setJoinedMsg(chat.getJoinedNick() + tempJoinedMsg);
			chat.setJoinToServer(true);

			std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
			gv->entitiesVec.emplace_back(new Clients(gv->consolasFont, gv->playerImage, tempPos, tempJoinedNick));

			for (auto& entity : gv->entitiesVec)
			{
				if (entity->getEntityType() == "Client")
				{
					if (entity->getName() == gv->getNickname())
					{
						currentClientID = tempID;
						setCurrentClient(entity.get());
						entity->getIcon().setFillColor(sf::Color::Green);
					}
					else { entity->getIcon().setFillColor(sf::Color::Magenta); }
					entity->getIcon().setPosition(entity->getSprite().getPosition());
				}
				tempID++;
			}
			playersList.updatePLScrollbar();
		}
		else if (prefix == L"disconnected")
		{
			std::wstring tempLeftMsg = L"", tempLeftNick = L"";
			chat.setLeftNick(L"");
			chat.setLeftMsg(L"");
			if (!(packet >> tempLeftNick && packet >> tempLeftMsg)) { DEBUG_MSG("prefix_disconnected_error!"); continue; }

			chat.setLeftNick(tempLeftNick);
			chat.setLeftMsg(chat.getLeftNick() + tempLeftMsg);

			std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
			gv->entitiesVec.erase(std::remove_if(gv->entitiesVec.begin(), gv->entitiesVec.end(), [&](std::unique_ptr<Entity>& entity) { return entity->getName() == chat.getLeftNick(); }), gv->entitiesVec.end());
			playersList.updatePLScrollbar();
			if (tempLeftNick != gv->getNickname())
			{
				chat.setChatStr(chat.getLeftMsg());
				chat.setLeftFromServer(true);
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

			chat.setSenderNickname(tempSenderNickname);
			chat.setChatStr(tempChatStr);
			chat.setNumOfLinesInChat(tempNumOfLinesInChat);
			chat.setRecvMsg(true);
		}

		sf::sleep(sf::milliseconds(1));
	}
	DEBUG_MSG("RECV DATA END");
}

void gameUpdate(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
	gv->setMenuNum(0);
	gv->setDT(gv->gameClock.restart().asSeconds());

	if (chat.getUserTextBox().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y)) { gv->setMenuNum(1); }
	chatUpdate(chat, gv->getNickname(), gv->getMousePos());
	callUpdateLaser(gv->getMousePos(), gv->aimLaser);

	if (gv->getServerIsNotAvailable() == true)
	{
		serverIsNotAvailable(gv);
		chat.getUserText().clear();
		chat.setChatEnterText(false);
		chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
		gv->OKButtonRS.setFillColor(sf::Color(255, 255, 255, 200));
		if (gv->OKButtonRS.getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) && gv->getServerIsNotAvailable() == true)
		{
			gv->setMenuNum(3);
			gv->OKButtonRS.setFillColor(sf::Color::White);
		}
	}

	std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
	playersList.updatePL(gv, Entity::getNumOfClients());
	chat.chatPosUpdate(getCurrentClientPos());
	gv->aimLaser.setPosition(getCurrentClientPos());
	gv->setGameViewCenter(getCurrentClientPos());
	if (gv->getShowMinimap() == true)
	{
		minimap.setViewCenter(sf::Vector2f((minimap.getView().getSize().x / 2.f) - 300.f, (minimap.getView().getSize().y / 2.f) - 250.f));
		minimap.setBorderPos(sf::Vector2f(gv->getGameViewCenter().x + (0.3f * gv->getGameViewSize().x), gv->getGameViewCenter().y - (0.5f * gv->getGameViewSize().y)));
	}
}

void minimapViewDraw(GameVariable* gv, Minimap& minimap)
{
	gv->setWindowView(minimap.getView());
	for (auto& entity : gv->entitiesVec)
	{
		if (entity->getEntityType() == "Client")
		{
			gv->window.draw(entity->getIcon());
		}
		else if (entity->getEntityType() == "Wall")
		{
			gv->window.draw(entity->getRectHitbox()); // draw rectangular hitboxes.
		}
	}
	gv->setWindowView(gv->getGameView());
}

void gameViewDraw(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	gv->setWindowView(gv->getGameView());
	for (auto& entity : gv->entitiesVec)
	{
		if (entity->getEntityType() == "Wall")
		{
			gv->window.draw(entity->getRectHitbox()); // draw rectangular hitboxes.
		}
		else if (entity->getEntityType() == "Client")
		{
			gv->window.draw(entity->getNameText());
			gv->window.draw(entity->getSprite());
			if (gv->getShowAimLaser() == true && gv->getFocusEvent() == true) { gv->window.draw(gv->aimLaser); }
		}
	}

	if (getCurrentClientIsMove() == true && gv->getServerIsNotAvailable() == false) { gv->window.draw(gv->playerDestination); }

	if (chat.getShowChat() == true)
	{
		gv->window.draw(chat.getOuterScrollBar());
		gv->window.draw(chat.getInnerScrollBar());
		gv->window.draw(chat.getChatTextBox());
		gv->window.draw(chat.getUserTextBox());
		gv->window.draw(chat.getUserText());
		gv->window.draw(chat.getChatText());
	}

	if (gv->getShowPlayersList() == true)
	{
		gv->window.draw(playersList.outerScrollBar);
		gv->window.draw(playersList.innerScrollBar);
		gv->window.draw(playersList.RS);
		gv->window.draw(playersList.text);
	}

	if (gv->getServerIsNotAvailable() == true)
	{
		gv->window.draw(gv->connectionErrorRS);
		gv->window.draw(gv->OKButtonRS);
		gv->window.draw(gv->connectionErrorText);
		gv->window.draw(gv->OKButtonText);
	}

	minimap.drawBorder(gv);
}

void gameDraw(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat)
{
	std::lock_guard<std::mutex> entities_lock(gv->entities_mtx);
	gv->window.clear(gv->backgroundColor);
	gameViewDraw(gv, minimap, playersList, chat);
	if (gv->getShowMinimap() == true) { minimapViewDraw(gv, minimap); }
}

void multiplayerGame(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // multiplayer game launch function.
{
	DEBUG_MSG("Your nickname is " << gv->getNickname());
	createWalls(gv);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		if (currentClientIsNullptr() == true) { /*DEBUG_MSG("client is nullptr!");*/ continue; }
		while (gv->window.pollEvent(gv->event))
		{
			m_eventHandler(gv, minimap, playersList, chat);
			if (checkConnection(gv) == false) { return; }
		}
		gameUpdate(gv, minimap, playersList, chat);
		gameDraw(gv, minimap, playersList, chat);
		gv->window.display();
	}
}

//void collisionForClients(Clients* client, Clients* client2)
//{
//	if (collision::areColliding(entity->sprite, client2->sprite))
//	{
//		if (entity->getEntityType() == "Box" || entity->getEntityType() == "Wall") // if the entity2 is a box or wall or enemy.
//		{
//			if (entity->getIsMove() == true) { entity->setIsMove(false); }
//			entity->setPosition(-(entity->getStepPos()));
//		}
//	}
//	//if (collision::areColliding(client, client2))
//	//{
//
//	//}
//	//if (collision::areColliding(entity, entity2))
//	//{
//	//	// if the entity is a bullet or box or player or enemy and creator name does not equal entity name.	
//	//	if (entity->getEntityType() == "Bullet" && (entity2->getEntityType() == "Box" || entity2->getEntityType() == "Player" || entity2->getEntityType() == "Wall") && entity->getCreatorName() != entity2->getName()) 
//	//	{
//	//		entity->setIsAlive(false);
//	//		entity2->setHP(entity2->getHP() - entity->getHP());
//	//	}
//	//}
//}
//void collisionForEntities(Clients* client, Clients* client2)
//{
//	if (collision::areColliding(entity->sprite, client2->sprite))
//	{
//		if (entity->getEntityType() == "Box" || entity->getEntityType() == "Wall") // if the entity2 is a box or wall or enemy.
//		{
//			if (entity->getIsMove() == true) { entity->setIsMove(false); }
//			entity->setPosition(-(entity->getStepPos()));
//		}
//	}
//	//if (collision::areColliding(client, client2))
//	//{
//
//	//}
//	//if (collision::areColliding(entity, entity2))
//	//{
//	//	// if the entity is a bullet or box or player or enemy and creator name does not equal entity name.	
//	//	if (entity->getEntityType() == "Bullet" && (entity2->getEntityType() == "Box" || entity2->getEntityType() == "Player" || entity2->getEntityType() == "Wall") && entity->getCreatorName() != entity2->getName()) 
//	//	{
//	//		entity->setIsAlive(false);
//	//		entity2->setHP(entity2->getHP() - entity->getHP());
//	//	}
//	//}
//}
//void updateGame()
//{
//	for (auto& el : gv->entitiesVec)
//	{
//		auto client = el.get();
//		for (auto& el2 : gv->entitiesVec)
//		{
//			auto client2 = el2.get();
//			collisionForClients(client, client2);
//		}
//	}
//
//	for (auto& el : gv->entitiesVec)
//	{
//		auto entity = el.get();
//		for (auto& el2 : gv->entitiesVec)
//		{
//			auto entity2 = el2.get();
//			collisionForEntities(entity, entity2);
//		}
//	}
//
//	for (auto& el : gv->entitiesVec)
//	{
//		auto client = el.get();
//		for (auto& el2 : gv->entitiesVec)
//		{
//			auto entity2 = el2.get();
//			collisionForEntitiesAndClients(client, entity);
//		}
//	}
//
//}