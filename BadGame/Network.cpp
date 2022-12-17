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

sf::UdpSocket sock;
std::vector<std::unique_ptr<Clients>> clientsVec; // vector unique pointers for clients.
std::mutex cVec_mtx;
std::mutex g_mtx;

PlayersList* playersListPtr = nullptr;
bool playerListEnabled = false;

void setSocketBlocking(bool blocking)
{
	g_mtx.lock();
	sock.setBlocking(blocking);
	g_mtx.unlock();
}

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec) // operator >> overload 
{
	cVec_mtx.lock();
	for (auto& client : clientsVec)
	{
		sf::Vector2f tempPos = sf::Vector2f(0.f, 0.f);

		packet >> client->id >> client->nickname >> tempPos.x >> tempPos.y;

		client->sprite.setPosition(tempPos);
		client->nickText.setString(client->nickname);
		client->nickText.setOrigin(round(client->nickText.getLocalBounds().left + (client->nickText.getLocalBounds().width / 2.f)), round(client->nickText.getLocalBounds().top + (client->nickText.getLocalBounds().height / 2.f)));
		client->nickText.setPosition(sf::Vector2f(client->sprite.getPosition().x, client->sprite.getPosition().y - 80.f));

	}
	cVec_mtx.unlock();
	return packet;
}

void enterMenu(GameVariable* gv, Entity*& player)
{
	sf::Vector2f oldViewSize(gv->getViewSize());
	sf::Vector2f oldViewCenter(gv->getViewCenter());
	menuEventHandler(gv, player);
	gv->setViewSize(oldViewSize);
	gv->setViewCenter(oldViewCenter);
	gv->window.setView(gv->getView());
}

void connectToServer(GameVariable* gv) // function to connect to the server.
{
	std::wstring prefix = L"regNick";
	sf::Packet packet;
	packet << prefix << gv->getNickname();
	sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void startNetwork(GameVariable* gv) // function to start network.
{
	sf::Clock connectionClock;
	float connectionTime;

	gv->setNetworkEnd(false);
	connectToServer(gv);
	connectionClock.restart();
	while (gv->window.isOpen())
	{
		if (gv->multiplayerError == MultiplayerErrors::NoErrors && gv->getNetworkEnd() == true)
		{
			DEBUG_MSG("You are connected!");
			break;
		}
		else if (gv->multiplayerError == MultiplayerErrors::NicknameIsAlreadyTaken)
		{
			DEBUG_MSG("Error: NicknameIsAlreadyTaken!");
			gv->setMultiPlayerGame(false);
			break;
		}
		connectionTime = connectionClock.getElapsedTime().asSeconds();
		if (connectionTime >= 3)
		{
			gv->multiplayerError = MultiplayerErrors::ServerIsNotAvailable;
			DEBUG_MSG("Error: ServerIsNotAvailable!");
			gv->setMultiPlayerGame(false);
			break;
		}
		sf::sleep(sf::milliseconds(1));
	}
	for (auto& el : gv->buttonsVec) { el->getSprite().setFillColor(sf::Color::White); }
	gv->setAllowButtons(true);
	gv->setNetworkEnd(true);
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
	sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void sendMoveRequest(GameVariable* gv) // sending a move request to the server
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"move";
	packet << prefix << gv->getNickname() << getClientStepPos().x << getClientStepPos().y;
	sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void sendMousePos(GameVariable* gv)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"mousePos";
	packet << prefix << gv->getNickname() << gv->getMousePos().x << gv->getMousePos().y;
	sock.send(packet, gv->getServerIP(), gv->getServerPort());
	sf::sleep(sf::milliseconds(3));
}

void resetVariables(GameVariable* gv) // global variable reset function.
{
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
	gv->setViewCenter(sf::Vector2f(960.f, 540.f));
	//setSocketBlocking(false);
	gv->gameClock.restart();
}

void eventHandler(GameVariable* gv, Chat& chat, Entity*& player)
{
	if (clientIsNullptr() == true) { return; }
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->setMultiPlayerGame(false);
		cVec_mtx.lock();
		clientsVec.clear();
		cVec_mtx.unlock();
		gv->window.close();
		break;
	case sf::Event::LostFocus:
		playerListEnabled = false;
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
				gv->setChatEnterText(false);
				chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
			}
			else if (gv->getMenuNum() == 1)
			{
				gv->setChatEnterText(true);
				setIsMove(false);
				chat.getUserTextBox().setFillColor(sf::Color::White);
			}
			if (gv->getChatEnterText() == false)
			{
				setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
				setIsMove(true);
				gv->playerDestination.setPosition(getMoveTargetPos()); // set the label position to the mouse click location.
				gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			}
			break;
		case sf::Mouse::Right:
			setIsShoot(true);
			break;
		}
		break;
	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Escape:
			playerListEnabled = false;
			gv->setInMenu(true);
			enterMenu(gv, player);
			gv->gameClock.restart();
			gv->setInMenu(false);
			break;
		case sf::Keyboard::O:
			if (gv->getChatEnterText() == false) { gv->setHideChat(!(gv->getHideChat())); }
			break;
		case sf::Keyboard::P:
			if (gv->getChatEnterText() == false) { /*gv->autoScroll = !gv->autoScroll;*/ }
			break;
		case sf::Keyboard::Tab:
			if (playerListEnabled == false) { playerListEnabled = true; }
			break;
		}
		break;

	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::C:
			if (gv->getChatEnterText() == false)
			{
				if (gv->getShowAimLaser() == false) { gv->setShowAimLaser(true); } // if the aiming laser was not shown - show.
				else { gv->setShowAimLaser(false); } // if the aiming laser was shown - don't show it.
			}
			break;
		case sf::Keyboard::Tab:
			if (playerListEnabled == true) { playerListEnabled = false; }
			break;
		}
		break;

	case sf::Event::MouseWheelMoved:

		if (gv->event.mouseWheel.delta == 1)
		{
			if ((chat.getStrVector().size() - chat.scrollbarStepNumber > 10) && chat.getStrVector().size() > 10 && gv->getChatContainsMouse() == true)
			{
				chat.scrollbarDir = L"up";
			}
			if (playersListPtr != nullptr && (clientsVec.size() - playersListPtr->getScrollbarStepNumber() > NUM_OF_DISPLAYED_PLAYERS))
			{
				playersListPtr->setScrollbarDir(L"up");
			}
		}
		else if (gv->event.mouseWheel.delta == -1)
		{
			if (chat.scrollbarStepNumber > 0 && chat.getStrVector().size() > 10 && gv->getChatContainsMouse() == true)
			{
				chat.scrollbarDir = L"down";
			}
			if (playersListPtr != nullptr && playersListPtr->getScrollbarStepNumber() > 0)
			{
				playersListPtr->setScrollbarDir(L"down");
			}
		}
		break;
	case sf::Event::TextEntered:
		if (gv->getChatEnterText() == true && gv->getHideChat() == false)
		{
			if (gv->event.text.unicode == BACKSPACE_CODE)
			{
				if (gv->getUserStr().size() > 0)
				{
					std::wstring tempStr = gv->getUserStr();
					tempStr.resize(gv->getUserStr().size() - 1);
					gv->setUserStr(tempStr);
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
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
					if (chat.trimString(tempUserStr, gv) == true)
					{
						gv->setSendMsg(true);
					}
					else
					{
						gv->setNumOfLinesInUserTextBox(1);
						chat.getUserText().clear();
						gv->setUserStr(L"");
					}
				}
			}
			else if (gv->event.text.unicode == QUESTION_MARK_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine(gv, chat);
					gv->setUserStr(gv->getUserStr() + L"\?");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == DOUBLE_QUOTES_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine(gv, chat);
					gv->setUserStr(gv->getUserStr() + L"\"");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == SINGLE_QUOTES_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine(gv, chat);
					gv->setUserStr(gv->getUserStr() + L"\'");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode == BACKSLASH_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine(gv, chat);
					gv->setUserStr(gv->getUserStr() + L"\\");
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
			else if (gv->event.text.unicode != BACKSPACE_CODE && gv->event.text.unicode != ESCAPE_CODE && gv->event.text.unicode != TABULATION_CODE)
			{
				if (gv->getUserStr().size() < CHAT_MAX_CHAR_NUM)
				{
					chat.addEndLine(gv, chat);
					std::wstring tempStr = gv->getUserStr();
					tempStr += gv->event.text.unicode;
					gv->setUserStr(tempStr);
					chat.getUserText().clear();
					chat.getUserText() << sf::Color::Black << gv->getUserStr();
				}
			}
		}
		break;
	}
}

void sendData(GameVariable* gv) // function to send data to the server.
{
	while (true)
	{
		if (gv == nullptr)
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("sendData: gv nullptr!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}
		if (gv->getMultiPlayerGame() == false && gv->getFuncName() == "multiplayerGame")
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("sendData: multiPlayerGame false!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}
		if (clientIsNullptr() == true && gv->getFuncName() == "multiplayerGame")
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("sendData: currentClient == nullptr!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}

		if (gv->getInMenu() == false && gv->getFocusEvent() == true && gv != nullptr && gv->getMultiPlayerGame() == true && clientIsNullptr() == false)
		{
			sendMousePos(gv);

			if (gv->getSendMsg() == true)
			{
				gv->setSendMsg(false);
				sendMessage(gv);
			}
			if (getClientIsMove() == true)
			{
				callMoveToTarget(gv);
				sendMoveRequest(gv);
			}
		}
		sf::sleep(sf::milliseconds(1));
	}
}

void receiveData(GameVariable* gv) // function to receive data from the server.
{
	sf::IpAddress serverIP = gv->getServerIP();
	unsigned short serverPort = gv->getServerPort();
	while (true)
	{
		sf::Packet packet;
		packet.clear();
		std::wstring prefix = L"";

		if (gv == nullptr)
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("receiveData: gv nullptr!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}
		if (gv->getMultiPlayerGame() == false)
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("receiveData: multiPlayerGame false!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}
		if (sock.receive(packet, serverIP, serverPort) != sf::Socket::Done)
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("sock receive error!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}
		if (!(packet >> prefix))
		{
			if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("prefix_error!"); }
			sf::sleep(sf::milliseconds(1));
			continue;
		}

		if (prefix == L"ping")
		{
			std::wstring tempNick = L"";
			if (!(packet >> tempNick)) { DEBUG_MSG("prefix_ping_error!"); continue; }

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (tempNick == client->nickname)
				{
					client->setClientPing(client->pingClock.restart().asMilliseconds() - gv->getPingDelay());
					if (client->getClientPing() < 0) { client->setClientPing(0); }

					packet.clear();
					packet << prefix << gv->getNickname();
					sock.send(packet, gv->getServerIP(), gv->getServerPort());
					break;
				}
			}
			cVec_mtx.unlock();
		}
		else if (prefix == L"conError_nickExists")
		{
			gv->multiplayerError = MultiplayerErrors::NicknameIsAlreadyTaken;
			gv->setMultiPlayerGame(false);
			gv->setNetworkEnd(true);
		}
		else if (prefix == L"regNick")
		{
			gv->multiplayerError = MultiplayerErrors::NoErrors;
			gv->setMultiPlayerGame(true);
			gv->setNetworkEnd(true);
		}
		else if (prefix == L"mousePos")
		{
			std::wstring tempNick = L"";
			sf::Vector2f tempMousePos;
			if (!(packet >> tempNick && packet >> tempMousePos.x && packet >> tempMousePos.y)) { DEBUG_MSG("prefix_clientUpdate_error!"); continue; }

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (client->nickname == tempNick)
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

			cVec_mtx.lock();
			for (auto& client : clientsVec)
			{
				if (client->nickname == tempNick)
				{
					client->sprite.move(tempStepPos);
					client->nickText.setPosition(client->sprite.getPosition().x, client->sprite.getPosition().y - 80.f);
					break;
				}
			}
			cVec_mtx.unlock();

			if (tempNick == gv->getNickname() && gv->getInMenu() == false)
			{
				if (playersListPtr != nullptr) { playersListPtr->updatePL(gv, cVec_mtx, clientsVec); }
				setWindowView(gv);
			}
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
			clientsVec.erase(std::remove_if(clientsVec.begin(), clientsVec.end(), [&](std::unique_ptr<Clients>& client) { return client->nickname == gv->getLeftNick(); }), clientsVec.end());
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
			if (!(packet >> clientsVecSize)) { DEBUG_MSG("prefix_clientsList_error!"); continue; }

			cVec_mtx.lock();
			clientsVec.clear();
			for (int i = 0; i < clientsVecSize; i++) { clientsVec.emplace_back(new Clients(gv)); }
			cVec_mtx.unlock();
			if (!(packet >> clientsVec)) { DEBUG_MSG("clientsVec not received!"); continue; }

			cVec_mtx.lock();
			for (auto& el : clientsVec)
			{
				if (el->nickname == gv->getNickname()) { setCurrentClient(el.get()); break; }
			}
			cVec_mtx.unlock();
		}
		else if (gv->getFuncName() == "multiplayerGame") { DEBUG_MSG("Reading error!"); }
		sf::sleep(sf::milliseconds(1));
	}
}

void setWindowView(GameVariable* gv)
{
	g_mtx.lock();
	gv->setViewCenter(getClientPos());
	gv->window.setView(gv->getView());
	g_mtx.unlock();
}

void gameUpdate(GameVariable* gv, Chat& chat, Entity*& player)
{
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
	gv->setMenuNum(0);
	gv->setDT(gv->gameClock.restart().asSeconds());
	chatUpdate(gv, chat);
	updateUserTextBox(gv, chat);
	updateScrollbarDir(gv, chat);
	callUpdateLaser(gv);
	if (playersListPtr != nullptr) { playersListPtr->updatePL(gv, cVec_mtx, clientsVec); }
	gv->aimLaser.setPosition(getClientPos());
}

void gameDraw(GameVariable* gv, Chat& chat)
{
	gv->window.clear(gv->backgroundColor);
	if (getClientIsMove() == true) { gv->window.draw(gv->playerDestination); }

	cVec_mtx.lock();
	for (auto& client : clientsVec)
	{
		gv->window.draw(client->sprite);
		gv->window.draw(client->nickText);
		if (gv->getShowAimLaser() == true && gv->getFocusEvent() == true) // if we show the aiming laser.
		{
			gv->window.draw(gv->aimLaser); // draw aiming laser.
		}
	}
	cVec_mtx.unlock();

	if (gv->getHideChat() == false)
	{
		gv->window.draw(chat.getOuterScrollBar());
		gv->window.draw(chat.getInnerScrollBar());
		gv->window.draw(chat.getChatTextBox());
		gv->window.draw(chat.getUserTextBox());
		gv->window.draw(chat.getUserText());
		gv->window.draw(chat.getChatText());
	}

	if (playersListPtr != nullptr && playerListEnabled == true)
	{
		playersListPtr->PL_mtx.lock();
		gv->window.draw(playersListPtr->outerScrollBar);
		gv->window.draw(playersListPtr->innerScrollBar);
		gv->window.draw(playersListPtr->RS);
		gv->window.draw(playersListPtr->text);
		playersListPtr->PL_mtx.unlock();
	}
	gv->window.display();
}

void multiplayerGame(GameVariable* gv, Entity*& player) // multiplayer game launch function.
{
	std::wcout << "Your nickname is " << gv->getNickname() << std::endl;
	Chat chat;
	PlayersList playersList;
	playersListPtr = &playersList;
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		if (clientIsNullptr() == true) { DEBUG_MSG("client is nullptr!\n"); continue; }

		gameUpdate(gv, chat, player);

		while (gv->window.pollEvent(gv->event))
		{
			eventHandler(gv, chat, player);
			if (checkConnection(gv) == false) { return; }
		}

		setWindowView(gv);
		gameDraw(gv, chat);
	}
}