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

std::vector<std::unique_ptr<Clients>> clientsVec; // vector unique pointers for clients.
std::vector<std::unique_ptr<Entity>> m_entitiesVec; // entities vector for multiplayer.

std::mutex cVec_mtx;
std::mutex g_mtx;

PlayersList* playersListPtr = nullptr;
Chat* chatPtr = nullptr;

bool isConnected = false;

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec) // operator >> overload 
{
	cVec_mtx.lock();
	for (auto& client : clientsVec)
	{
		sf::Vector2f tempPos = sf::Vector2f(0.f, 0.f);
		int tempId = 0;
		std::wstring tempNick = L"";

		packet >> tempId >> tempNick >> tempPos.x >> tempPos.y;

		client->setId(tempId);
		client->setNickname(tempNick);
		client->sprite.setPosition(tempPos);
		client->nickText.setString(client->getNickname());
		client->nickText.setOrigin(round(client->nickText.getLocalBounds().left + (client->nickText.getLocalBounds().width / 2.f)), round(client->nickText.getLocalBounds().top + (client->nickText.getLocalBounds().height / 2.f)));
		client->nickText.setPosition(sf::Vector2f(client->sprite.getPosition().x, client->sprite.getPosition().y - 80.f));
	}
	cVec_mtx.unlock();
	return packet;
}

void createWalls()
{
	m_entitiesVec.clear();
	m_entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"LeftWall", wallSize)); // create a left wall and throw it into the list of entities.
	m_entitiesVec.emplace_back(new Wall(sf::Vector2f(5000.f, 0.f), L"RightWall", wallSize)); // create a right wall and throw it into the list of entities.
	m_entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"TopWall", wallSize)); // create a top wall and throw it into the list of entities.
	m_entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 4936.f), L"BottomWall", wallSize)); // create a bottom wall and throw it into the list of entities.
}

void serverIsNotAvailable(GameVariable* gv)
{
	gv->connectionErrorRS.setSize(sf::Vector2f(1000.f, 300.f));
	gv->connectionErrorRS.setFillColor(sf::Color(0, 0, 0, 200));
	gv->connectionErrorRS.setOrigin(gv->connectionErrorRS.getSize() / 2.f);
	g_mtx.lock();
	gv->connectionErrorRS.setPosition(getCurrentClientPos());
	g_mtx.unlock();
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

void m_enterMenu(GameVariable* gv, Minimap& minimap) // enter menu for multiplayer.
{
	gv->setShowPlayersList(false);
	gv->setInMenu(true);

	menuEventHandler(gv, minimap);

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
			isConnected = true;
			break;
		}
		else if (gv->multiplayerError == MultiplayerErrors::NicknameIsAlreadyTaken)
		{
			DEBUG_MSG("Error: NicknameIsAlreadyTaken!");
			gv->setMultiPlayerGame(false);
			isConnected = false;
			break;
		}
		connectionTime = connectionClock.getElapsedTime().asSeconds();
		if (connectionTime >= 3)
		{
			gv->multiplayerError = MultiplayerErrors::ServerIsNotAvailable;
			DEBUG_MSG("Error: ServerIsNotAvailable!");
			gv->setMultiPlayerGame(false);
			isConnected = false;
			break;
		}
		sf::sleep(sf::milliseconds(1));
	}
	gv->setConnectsToServer(false);
}

bool checkConnection(GameVariable* gv)
{
	if (gv->getMultiPlayerGame() == false)
	{
		cVec_mtx.lock();
		clientsVec.clear();
		cVec_mtx.unlock();

		DEBUG_MSG("You are disconnected!");
		return false;
	}
	else { return true; }
}

void sendMessage(GameVariable* gv) // function to send message to the server.
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"msg";
	packet << prefix << gv->getNickname() << gv->getUserStr() << gv->getNumOfLinesInUserTextBox();
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

void m_resetVariables(GameVariable* gv) // global variable reset function for multiplayer.
{
	gv->setServerIsNotAvailable(false);
	gv->setInMenu(false);
	gv->setShowPlayersList(false);
	gv->setShowChat(true);
	gv->setUserStr(L"");
	gv->setChatStr(L"");
	gv->setChatPrefix(L"");
	gv->setJoinedMsg(L"");
	gv->setLeftMsg(L"");
	gv->setNumOfLinesInChat(1);
	gv->setNumOfLinesInUserTextBox(1);
	gv->setChatEnterText(false);
	gv->setChatContainsMouse(false);
	gv->setRecvMsg(false);
	gv->setSendMsg(false);
	gv->setLeftFromServer(false);
	gv->setJoinToServer(true);
	gv->setShowMinimap(true);
	gv->gameClock.restart();
}

void m_eventHandler(GameVariable* gv, Minimap& minimap) // event handler for multiplayer.
{
	if (currentClientIsNullptr() == true) { return; }
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->setMultiPlayerGame(false);
		clientsVec.clear();
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
				gv->setMultiPlayerGame(false);
				gv->setMenuNum(0);
				return;
			}
			if (gv->getMenuNum() == 0 && gv->getServerIsNotAvailable() == false)
			{
				gv->setChatEnterText(false);
				chatPtr->getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
			}
			else if (gv->getMenuNum() == 1 && gv->getServerIsNotAvailable() == false)
			{
				gv->setChatEnterText(true);
				setCurrentClientIsMove(false);
				chatPtr->getUserTextBox().setFillColor(sf::Color::White);
			}
			if (gv->getChatEnterText() == false)
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
			//	if (gv->getChatEnterText() == false) { gv->setChatAutoScroll(!(gv->getChatAutoScroll())); }
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
			if (gv->getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { gv->setShowAimLaser(!(gv->getShowAimLaser())); }
			break;
		case sf::Keyboard::Tab:
			if (gv->getShowPlayersList() == true) { gv->setShowPlayersList(false); }
			break;
		case sf::Keyboard::Escape:
			m_enterMenu(gv, minimap);
			break;
		case sf::Keyboard::O:
			if (gv->getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { gv->setShowChat(!(gv->getShowChat())); }
			break;
		case sf::Keyboard::M:
			if (gv->getChatEnterText() == false && gv->getServerIsNotAvailable() == false) { gv->setShowMinimap(!(gv->getShowMinimap())); }
			break;
		}
		break;
	case sf::Event::MouseWheelMoved:
		if (gv->event.mouseWheel.delta == 1)
		{
			if (((chatPtr->getStrVector().size() - chatPtr->getScrollbarStepNumber()) > 10) && chatPtr->getStrVector().size() > 10 && gv->getChatContainsMouse() == true && gv->getShowChat() == true)
			{
				chatPtr->setScrollbarDir(L"up");
			}
			if (playersListPtr != nullptr && ((clientsVec.size() - playersListPtr->getScrollbarStepNumber()) > NUM_OF_DISPLAYED_PLAYERS) && gv->getShowPlayersList() == true)
			{
				playersListPtr->setScrollbarDir(L"up");
			}
		}
		else if (gv->event.mouseWheel.delta == -1)
		{
			if (chatPtr->getScrollbarStepNumber() > 0 && chatPtr->getStrVector().size() > 10 && gv->getChatContainsMouse() == true && gv->getShowChat() == true)
			{
				chatPtr->setScrollbarDir(L"down");
			}
			if (playersListPtr != nullptr && playersListPtr->getScrollbarStepNumber() > 0 && gv->getShowPlayersList() == true)
			{
				playersListPtr->setScrollbarDir(L"down");
			}
		}
		break;
	case sf::Event::TextEntered:
		if (gv->getChatEnterText() == true && gv->getShowChat() == true)
		{
			if (gv->event.text.unicode == BACKSPACE_CODE)
			{
				if (gv->getUserStr().size() > 0)
				{
					std::wstring tempStr = gv->getUserStr();
					tempStr.resize(gv->getUserStr().size() - 1);
					gv->setUserStr(tempStr);
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
					if (!gv->getUserStr().empty())
					{
						if (gv->getUserStr()[gv->getUserStr().size() - 1] == '\n')
						{
							tempStr = gv->getUserStr();
							tempStr.resize(gv->getUserStr().size() - 1);
							gv->setUserStr(tempStr);
							gv->setNumOfLinesInUserTextBox(gv->getNumOfLinesInUserTextBox() - 1);
						}
					}
				}
			}
			else if (gv->event.text.unicode == ENTER_CODE)
			{
				if (gv->getUserStr().size() > 0 && gv->getUserStr().size() <= CHAT_MAX_CHAR_NUM && gv->getSendMsg() == false && gv->getRecvMsg() == false)
				{
					std::wstring tempUserStr = gv->getUserStr();
					if (chatPtr->trimString(tempUserStr, gv) == true)
					{
						gv->setSendMsg(true);
					}
					else
					{
						gv->setNumOfLinesInUserTextBox(1);
						chatPtr->getUserText().clear();
						gv->setUserStr(L"");
					}
				}
			}
			else if (gv->event.text.unicode == QUESTION_MARK_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chatPtr->addEndLine(gv);
					gv->setUserStr(gv->getUserStr() + L"\?");
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == DOUBLE_QUOTES_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chatPtr->addEndLine(gv);
					gv->setUserStr(gv->getUserStr() + L"\"");
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == SINGLE_QUOTES_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chatPtr->addEndLine(gv);
					gv->setUserStr(gv->getUserStr() + L"\'");
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == BACKSLASH_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chatPtr->addEndLine(gv);
					gv->setUserStr(gv->getUserStr() + L"\\");
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode != BACKSPACE_CODE && gv->event.text.unicode != ESCAPE_CODE && gv->event.text.unicode != TABULATION_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chatPtr->addEndLine(gv);
					std::wstring tempStr = gv->getUserStr();
					tempStr += gv->event.text.unicode;
					gv->setUserStr(tempStr);
					chatPtr->getUserText().clear();
					chatPtr->getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
		}
		break;
	}
}

void sendData(GameVariable* gv) // function to send data to the server.
{
	DEBUG_MSG("SEND DATA START");
	while (gv->getMultiPlayerGame() == true)
	{
		if (gv == nullptr) { DEBUG_MSG("sendData: gv == nullptr"); sf::sleep(sf::milliseconds(1)); continue; }
		if (gv->getInMenu() == true) { DEBUG_MSG("sendData: gv->getInMenu() == true"); sf::sleep(sf::milliseconds(1)); continue; }
		if (gv->getFocusEvent() == false) { DEBUG_MSG("sendData: gv->getFocusEvent() == false"); sf::sleep(sf::milliseconds(1)); continue; }
		if (currentClientIsNullptr() == true) { DEBUG_MSG("sendData: clientIsNullptr() == true"); sf::sleep(sf::milliseconds(1)); continue; }

		if (isConnected == true)
		{
			sendMousePos(gv);
			if (gv->getSendMsg() == true)
			{
				gv->setSendMsg(false);
				sendMessage(gv);
			}
			if (getCurrentClientIsMove() == true)
			{
				callMoveToTarget(gv);
				sendMoveRequest(gv);
			}
		}

		sf::sleep(sf::milliseconds(1));
	}
	DEBUG_MSG("SEND DATA END");
}

void receiveData(GameVariable* gv) // function to receive data from the server.
{
	DEBUG_MSG("RECV DATA START");
	sf::IpAddress serverIP = gv->getServerIP();
	unsigned short serverPort = gv->getServerPort();
	while (gv->getMultiPlayerGame() == true)
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

		if (gv->sock.receive(packet, serverIP, serverPort) != sf::Socket::Done) { DEBUG_MSG("recvData: sock receive error"); sf::sleep(sf::milliseconds(1)); continue; }
		if ((!(packet >> prefix))) { DEBUG_MSG("recvData: packet >> prefix error"); sf::sleep(sf::milliseconds(1)); continue; }
		if (gv == nullptr) { DEBUG_MSG("recvData: gv == nullptr"); sf::sleep(sf::milliseconds(1)); continue; }

		if (prefix == L"ping")
		{
			std::wstring tempNick = L"";
			if (!(packet >> tempNick)) { DEBUG_MSG("prefix_ping_error!"); continue; }

			gv->restartServerClock();

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (tempNick == client->getNickname())
				{
					client->setPing(client->pingClock.restart().asMilliseconds() - gv->getPingDelay());
					if (client->getPing() < 0) { client->setPing(0); }

					packet.clear();
					packet << prefix << gv->getNickname();
					gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
					break;
				}
			}
			cVec_mtx.unlock();
		}
		else if (prefix == L"conError_nickExists")
		{
			gv->multiplayerError = MultiplayerErrors::NicknameIsAlreadyTaken;
			gv->setMultiPlayerGame(false);
			gv->setConnectsToServer(false);
		}
		else if (prefix == L"regNick")
		{
			gv->multiplayerError = MultiplayerErrors::NoErrors;
			gv->setMultiPlayerGame(true);
			gv->setConnectsToServer(false);
		}
		else if (prefix == L"mousePos")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempMousePos;
			if (!(packet >> tempNick && packet >> tempMousePos.x && packet >> tempMousePos.y)) { DEBUG_MSG("prefix_clientUpdate_error!"); continue; }

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (client->getNickname() == tempNick)
				{
					client->rotate(gv, tempMousePos);
					break;
				}
			}
			cVec_mtx.unlock();
		}
		else if (prefix == L"move")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempStepPos;
			if (!(packet >> tempNick && packet >> tempStepPos.x && packet >> tempStepPos.y)) { DEBUG_MSG("prefix_move_error!"); continue; }

			g_mtx.lock();

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (client->getNickname() == tempNick)
				{
					client->setPosition(tempStepPos);
					client->setNickPosition();
					break;
				}
			}
			cVec_mtx.unlock();

			if (tempNick == gv->getNickname())
			{
				if (playersListPtr != nullptr) { playersListPtr->updatePL(gv, cVec_mtx, clientsVec); }
				if (chatPtr != nullptr) { chatPtr->chatPosUpdate(getCurrentClientPos()); }
			}

			g_mtx.unlock();
		}
		else if (prefix == L"connected")
		{
			std::wstring tempJoinedMsg = L"", tempJoinedNick = L"";
			gv->setJoinedNick(L"");
			gv->setJoinedMsg(L"");
			if (!(packet >> tempJoinedNick && packet >> tempJoinedMsg)) { DEBUG_MSG("prefix_connected_error!"); continue; }

			gv->setJoinedNick(tempJoinedNick);
			gv->setJoinedMsg(gv->getJoinedNick() + tempJoinedMsg);
			gv->setJoinToServer(true);

			if (playersListPtr != nullptr && tempJoinedNick != gv->getNickname()) { playersListPtr->updatePLScrollbar(); }
		}
		else if (prefix == L"disconnected")
		{
			std::wstring tempLeftMsg = L"", tempLeftNick = L"";
			gv->setLeftNick(L"");
			gv->setLeftMsg(L"");
			if (!(packet >> tempLeftNick && packet >> tempLeftMsg)) { DEBUG_MSG("prefix_disconnected_error!"); continue; }

			gv->setLeftNick(tempLeftNick);
			gv->setLeftMsg(gv->getLeftNick() + tempLeftMsg);

			cVec_mtx.lock();
			clientsVec.erase(std::remove_if(clientsVec.begin(), clientsVec.end(), [&](std::unique_ptr<Clients>& client) { return client->getNickname() == gv->getLeftNick(); }), clientsVec.end());
			cVec_mtx.unlock();

			if (tempLeftNick != gv->getNickname())
			{
				gv->setChatStr(gv->getLeftMsg());
				gv->setLeftFromServer(true);
				if (playersListPtr != nullptr) { playersListPtr->updatePLScrollbar(); }
			}
		}
		else if (prefix == L"msg")
		{
			gv->setSenderNickname(L"");
			gv->setChatStr(L"");
			gv->setNumOfLinesInChat(1);
			std::wstring tempChatStr = L"";
			std::wstring tempSenderNickname = L"";
			int tempNumOfLinesInChat = 0;

			if (!(packet >> tempSenderNickname && packet >> tempChatStr && packet >> tempNumOfLinesInChat)) { DEBUG_MSG("prefix_msg_error!"); continue; }

			gv->setSenderNickname(tempSenderNickname);
			gv->setChatStr(tempChatStr);
			gv->setNumOfLinesInChat(tempNumOfLinesInChat);
			gv->setRecvMsg(true);
		}
		else if (prefix == L"clientsList")
		{
			sf::Uint64 clientsVecSize = 0;
			int currentClientID = 0;
			if (!(packet >> clientsVecSize)) { DEBUG_MSG("prefix_clientsList_error!"); continue; }

			cVec_mtx.lock();
			clientsVec.clear();
			for (int i = 0; i < clientsVecSize; i++) { clientsVec.emplace_back(new Clients(gv)); }
			cVec_mtx.unlock();
			if (!(packet >> clientsVec)) { DEBUG_MSG("clientsVec not received!"); continue; }

			cVec_mtx.lock();
			for (int i = 0; i < clientsVec.size(); i++)
			{
				if (clientsVec[i]->getNickname() == gv->getNickname())
				{
					currentClientID = i;
					setCurrentClient(clientsVec[i].get());
					clientsVec[i]->icon.setFillColor(sf::Color::Green);
				}
				else { clientsVec[i]->icon.setFillColor(sf::Color::Magenta); }
				clientsVec[i]->icon.setPosition(clientsVec[i]->sprite.getPosition());
			}
			std::swap(clientsVec[currentClientID], clientsVec[clientsVec.size() - 1]);
			cVec_mtx.unlock();
		}
		else { DEBUG_MSG("Reading error!"); }
		sf::sleep(sf::milliseconds(1));
	}
	DEBUG_MSG("RECV DATA END");
}

void gameUpdate(GameVariable* gv)
{
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
	gv->setMenuNum(0);
	gv->setDT(gv->gameClock.restart().asSeconds());
	chatUpdate(gv, *chatPtr);
	updateUserTextBox(gv, *chatPtr);
	updateScrollbarDir(gv, *chatPtr);
	callUpdateLaser(gv);

	g_mtx.lock();
	if (playersListPtr != nullptr) { playersListPtr->updatePL(gv, cVec_mtx, clientsVec); }
	if (chatPtr != nullptr) { chatPtr->chatPosUpdate(getCurrentClientPos()); }
	gv->aimLaser.setPosition(getCurrentClientPos());
	g_mtx.unlock();

	if (gv->getServerIsNotAvailable() == true)
	{
		serverIsNotAvailable(gv);
		chatPtr->getUserText().clear();
		gv->setChatEnterText(false);
		chatPtr->getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
	}
	gv->OKButtonRS.setFillColor(sf::Color(255, 255, 255, 200));
	if (gv->OKButtonRS.getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) && gv->getServerIsNotAvailable() == true)
	{
		gv->setMenuNum(3);
		gv->OKButtonRS.setFillColor(sf::Color::White);
	}
}

void minimapViewDraw(GameVariable* gv)
{
	cVec_mtx.lock();
	for (auto& client : clientsVec)
	{
		gv->window.draw(client->icon);
	}
	cVec_mtx.unlock();

	for (auto& el : m_entitiesVec)
	{
		gv->window.draw(el->getRectHitbox()); // draw rectangular hitboxes.
	}
}

void gameViewDraw(GameVariable* gv, Minimap& minimap)
{
	for (auto& el : m_entitiesVec)
	{
		gv->window.draw(el->getRectHitbox()); // draw rectangular hitboxes.
	}

	if (getCurrentClientIsMove() == true && gv->getServerIsNotAvailable() == false) { gv->window.draw(gv->playerDestination); }

	cVec_mtx.lock();
	for (auto& client : clientsVec)
	{
		gv->window.draw(client->sprite);
		gv->window.draw(client->nickText);
		if (gv->getShowAimLaser() == true && gv->getFocusEvent() == true) { gv->window.draw(gv->aimLaser); }
	}
	cVec_mtx.unlock();

	if (gv->getShowChat() == true)
	{
		gv->window.draw(chatPtr->getOuterScrollBar());
		gv->window.draw(chatPtr->getInnerScrollBar());
		gv->window.draw(chatPtr->getChatTextBox());
		gv->window.draw(chatPtr->getUserTextBox());
		gv->window.draw(chatPtr->getUserText());
		gv->window.draw(chatPtr->getChatText());
	}

	if (playersListPtr != nullptr && gv->getShowPlayersList() == true)
	{
		playersListPtr->PL_mtx.lock();
		gv->window.draw(playersListPtr->outerScrollBar);
		gv->window.draw(playersListPtr->innerScrollBar);
		gv->window.draw(playersListPtr->RS);
		gv->window.draw(playersListPtr->text);
		playersListPtr->PL_mtx.unlock();
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

void gameDraw(GameVariable* gv, Minimap& minimap)
{
	gv->window.clear(gv->backgroundColor);

	g_mtx.lock();

	gv->setGameViewCenter(getCurrentClientPos());
	if (gv->getShowMinimap() == true)
	{
		minimap.setViewCenter(sf::Vector2f((minimap.getView().getSize().x / 2.f) - 300.f, (minimap.getView().getSize().y / 2.f) - 250.f));
		minimap.setBorderPos(sf::Vector2f(gv->getGameViewCenter().x + (0.3f * gv->getGameViewSize().x), gv->getGameViewCenter().y - (0.5f * gv->getGameViewSize().y)));
	}

	gv->setWindowView(gv->getGameView());
	gameViewDraw(gv, minimap);

	if (gv->getShowMinimap() == true)
	{
		gv->setWindowView(minimap.getView());
		minimapViewDraw(gv);
		gv->setWindowView(gv->getGameView());
	}

	g_mtx.unlock();

	gv->window.display();
}

void multiplayerGame(GameVariable* gv, Minimap& minimap) // multiplayer game launch function.
{
	DEBUG_MSG("Your nickname is " << gv->getNickname());
	Chat chat;
	PlayersList playersList;
	chatPtr = &chat;
	playersListPtr = &playersList;
	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(0.f, 0.f));
	gv->setWindowView(gv->getGameView());
	createWalls();
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		if (currentClientIsNullptr() == true) { DEBUG_MSG("client is nullptr!"); continue; }
		while (gv->window.pollEvent(gv->event))
		{
			m_eventHandler(gv, minimap);
			if (checkConnection(gv) == false) { return; }
		}
		gameUpdate(gv);
		gameDraw(gv, minimap);
	}
}