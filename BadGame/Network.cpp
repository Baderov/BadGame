#include "Network.h"

//ip - "127.0.0.1";
//port - 2000;

HANDLE handle;

std::wstring senderNickname = L"";
sf::Uint64 clientsVecSize = 0;

bool isConnected = false;
bool allowMove = false;
bool isVectorReceived = false;
bool isNickTaken = false;
bool hideChat = false;
std::wstring movement = L"";

Clients::Clients(int id, std::wstring nickname, sf::Vector2f pos)
{
	this->id = id;
	this->nickname = nickname;
	this->pos = pos;
}

Clients::Clients()
{
	this->id = 0;
	this->nickname = L"";
	this->pos = sf::Vector2f(0.f, 0.f);
}

std::vector<std::unique_ptr<Clients>> clientsVec; // вектор структур для клиентов.
std::vector<std::unique_ptr<Clients>> tempVec; // вектор структур для клиентов.

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec)
{
	for (auto& el : clientsVec)
	{
		packet >> el->id >> el->nickname >> el->pos.x >> el->pos.y;
	}
	return packet;
}

bool connectToServer(GameVariables* gv)
{
	if (gv->sock.connect(gv->serverIP, gv->serverPort) == sf::Socket::Done) // подключение к серверу, нужно ввести ip и порт.
	{
		sf::Packet packet;
		std::wstring prefix = L"regNickname"; // regNickname - register a nickname.
		packet << prefix << gv->nickname;
		gv->sock.send(packet); // отправка данных
		SetConsoleTextAttribute(handle, 13);
		return true;
	}
	else
	{
		return false;
	}
}

void receive(GameVariables* gv)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	std::wstring prefix = L"", msg = L"", side = L"";
	while (true)
	{
		if (gv->isGameOver == true)
		{
			break;
		}
		if (gv->sock.receive(packet) == sf::Socket::Done)
		{
			msg = L"";
			prefix = L"";
			if (packet >> prefix)
			{
				if (prefix == L"conError")
				{
					isNickTaken = true;
					gv->menuError = MenuErrors::NicknameIsAlreadyTaken;
					gv->multiPlayerGame = false;
				}
				else if (prefix == L"conSuccess")
				{
					isNickTaken = false;
					gv->menuError = MenuErrors::NoErrors;
					gv->multiPlayerGame = true;
				}
				else if (prefix == L"con") // con - connected.
				{
					std::wstring tempMsg = L"";
					gv->joinedNick = L"";
					gv->joinedMsg = L"";
					if (packet >> gv->joinedNick && packet >> tempMsg)
					{
						gv->joinedMsg = gv->joinedNick + tempMsg;
						gv->joinToServer = true;
					}
				}
				else if (prefix == L"discon") // discon - disconnected.
				{
					std::wstring tempMsg = L"";
					gv->leftNick = L"";
					gv->leftMsg = L"";
					if (packet >> gv->leftNick && packet >> tempMsg)
					{
						gv->leftMsg = gv->leftNick + tempMsg;
						gv->leftFromServer = true;
					}
				}
				else if (prefix == L"move")
				{
					std::wstring tempNick = L"";
					if (packet >> allowMove && packet >> side && packet >> tempNick)
					{
						for (auto& el : clientsVec)
						{
							if (el->nickname == tempNick && allowMove == true)
							{
								if (side == L"up")
								{
									el->playerShape.move(0.f, -5.f);
								}
								else if (side == L"down")
								{
									el->playerShape.move(0.f, 5.f);
								}
								else if (side == L"left")
								{
									el->playerShape.move(-5.f, 0.f);
								}
								else if (side == L"right")
								{
									el->playerShape.move(5.f, 0.f);
								}
								el->nickText.setPosition(el->playerShape.getPosition().x, el->playerShape.getPosition().y - 80.f);
							}
						}
					}
				}
				else if (prefix == L"pos")
				{
					std::wstring tempNick = L"";
					sf::Vector2f tempPos;
					if (packet >> tempNick && packet >> tempPos.x && packet >> tempPos.y)
					{
						for (auto& el : clientsVec)
						{
							if (el->nickname == tempNick)
							{
								el->pos = tempPos;
							}
						}
					}
				}
				else if (prefix == L"msg")
				{
					senderNickname = L"";
					gv->chatStr = L"";
					gv->numOfLinesInChat = 1;
					if (packet >> senderNickname && packet >> gv->chatStr && packet >> gv->numOfLinesInChat)
					{
						gv->recvMsg = true;
					}
				}
				else if (prefix == L"clientsList")
				{
					if (packet >> clientsVecSize)
					{				
						tempVec.clear();
						for (int i = 0; i < clientsVecSize; i++)
						{
							tempVec.emplace_back(new Clients()); // создание пустых объектов вектора.
						}
						if (packet >> tempVec)
						{
							isVectorReceived = true;
						}
					}
					packet.clear(); // чистим пакет
				}
				else
				{
					std::cout << "Reading error!" << std::endl;
					packet.clear(); // чистим пакет
				}
			}
		}
	}
}

void sendMessage(GameVariables* gv)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::wstring prefix = L"msg";
	packet << prefix << gv->nickname << gv->userStr << gv->numOfLinesInUserTextBox;
	gv->sock.send(packet);
}

void moveRequest(GameVariables* gv, std::wstring side)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::wstring prefix = L"move";
	packet << prefix << side << gv->nickname;
	gv->sock.send(packet);
}

void sendPosition(GameVariables* gv)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::wstring prefix = L"pos";
	sf::Vector2f pos;
	for (auto& el : clientsVec)
	{
		if (el->nickname == gv->nickname)
		{
			pos = el->playerShape.getPosition();
			break;
		}
	}
	packet << prefix << gv->nickname << pos.x << pos.y;
	gv->sock.send(packet);
}

void send(GameVariables* gv)
{
	while (true)
	{
		if (gv->isGameOver == true)
		{
			break;
		}
		if (gv->sendMsg == true)
		{
			gv->sendMsg = false;
			sendMessage(gv);
		}
		if (movement == L"up")
		{
			sendPosition(gv);
			moveRequest(gv, L"up");
			movement = L"";
		}
		else if (movement == L"down")
		{
			sendPosition(gv);
			moveRequest(gv, L"down");
			movement = L"";
		}
		else if (movement == L"left")
		{
			sendPosition(gv);
			moveRequest(gv, L"left");
			movement = L"";
		}
		else if (movement == L"right")
		{
			sendPosition(gv);
			moveRequest(gv, L"right");
			movement = L"";
		}
	}
}

void fillClientsVector(GameVariables* gv)
{
	if (isVectorReceived == true)
	{
		clientsVec.clear();
		for (int i = 0; i < tempVec.size(); i++)
		{
			clientsVec.emplace_back(new Clients(tempVec[i].get()->id, tempVec[i].get()->nickname, tempVec[i].get()->pos));
		}

		for (auto& el : clientsVec)
		{
			el->playerShape.setSize(sf::Vector2f(100.f, 100.f));
			el->playerShape.setFillColor(sf::Color::Black);
			el->playerShape.setOrigin(el->playerShape.getSize() / 2.f);
			el->playerShape.setPosition(el->pos);

			el->nickText.setFont(gv->consolasFont);
			el->nickText.setFillColor(sf::Color::Green);
			el->nickText.setCharacterSize(40);
			el->nickText.setOutlineThickness(2.f);
			el->nickText.setString(el->nickname);
			el->nickText.setOrigin(round(el->nickText.getLocalBounds().left + (el->nickText.getLocalBounds().width / 2.f)), round(el->nickText.getLocalBounds().top + (el->nickText.getLocalBounds().height / 2.f)));
			el->nickText.setPosition(el->playerShape.getPosition().x, el->playerShape.getPosition().y - 80.f);
		}
		isVectorReceived = false;
	}
}

void startNetwork(GameVariables* gv)
{
	std::thread receiveThread([&]() { receive(gv); });
	receiveThread.detach();
	if (connectToServer(gv) == true)
	{
		gv->allowButtons = true;
		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}
	}
	else
	{
		gv->allowButtons = true;
		gv->menuError = MenuErrors::ServerIsNotAvailable;
		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}
		gv->multiPlayerGame = false;
	}
	gv->isGameOver = true;

}

void updateVariables(GameVariables* gv)
{
	gv->userStr = L"";
	gv->chatStr = L"";
	gv->chatPrefix = L"";
	gv->scrollbarDir = L"";
	gv->leftNick = L"";
	gv->leftMsg = L"";
	gv->joinedNick = L"";
	gv->joinedMsg = L"";
	gv->numOfLinesInChat = 1;
	gv->numOfLinesInUserTextBox = 1;
	gv->scrollbarDivisor = 1;
	gv->scrollbarStepNumber = 0;
	gv->chatEnterText = false;
	gv->chatContainsMouse = false;
	gv->recvMsg = false;
	gv->sendMsg = false;
	gv->leftFromServer = false;
	gv->joinToServer = false;
}

void multiplayerGame(GameVariables* gv, Entity*& player)
{
	updateVariables(gv);

	Chat chat(gv->window);

	std::thread receiveThread([&]() { receive(gv); });
	std::thread sendThread([&]() { send(gv); });

	receiveThread.detach();
	sendThread.detach();

	while (gv->window.isOpen()) // пока меню открыто.
	{
		fillClientsVector(gv);
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0;

		if (gv->leftFromServer == true)
		{
			clientsVec.erase(std::remove_if(clientsVec.begin(), clientsVec.end(), [&](std::unique_ptr<Clients>& client) { return client.get()->nickname == gv->leftNick; }), clientsVec.end());
			gv->chatStr = gv->leftMsg;
			chat.addString(gv, chat);
			gv->leftFromServer = false;
		}
		if (gv->joinToServer == true)
		{
			gv->chatStr = gv->joinedMsg;
			chat.addString(gv, chat);
			gv->joinToServer = false;
		}

		if (gv->recvMsg == true)
		{
			gv->chatPrefix = senderNickname + L": ";
			chat.addString(gv, chat);
			if (gv->nickname == senderNickname)
			{
				gv->numOfLinesInUserTextBox = 1;
				chat.getUserText().clear();
				gv->userStr = L"";
			}
			gv->sendMsg = false;
			gv->recvMsg = false;
		}

		if (chat.getUserTextBox().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
		{
			gv->menuNum = 1;
		}

		if (chat.getUserTextBox().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y) || chat.getChatTextBox().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y) || chat.getOuterScrollBar().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y) || chat.getInnerScrollBar().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
		{
			gv->chatContainsMouse = true;
		}
		else
		{
			gv->chatContainsMouse = false;
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::Closed) { clientsVec.clear(); tempVec.clear(); gv->window.close(); } // если состояние события приняло значение "Закрыто" - окно закрывается.

			if (gv->event.type == sf::Event::LostFocus)
			{
				gv->focusEvent = false;
			}

			else if (gv->event.type == sf::Event::GainedFocus)
			{
				gv->focusEvent = true;
			}

			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left)
			{
				if (gv->menuNum == 0)
				{
					gv->chatEnterText = false;
					chat.getUserTextBox().setFillColor(sf::Color(0, 0, 0, 100));
				}
				else if (gv->menuNum == 1)
				{
					gv->chatEnterText = true;
					chat.getUserTextBox().setFillColor(sf::Color::White);
				}
			}

			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				menuEventHandler(gv, player);
				if (gv->multiPlayerGame == false) { gv->exitFromMenu = true; gv->isGameOver = true; return; }
			}

			if (gv->event.type == sf::Event::MouseWheelMoved && chat.getStrVector().size() > 10 && gv->chatContainsMouse == true)
			{
				if (gv->event.mouseWheel.delta == 1 && chat.getStrVector().size() - gv->scrollbarStepNumber > 10)
				{
					gv->scrollbarDir = L"up";
				}
				else if (gv->event.mouseWheel.delta == -1 && gv->scrollbarStepNumber > 0)
				{
					gv->scrollbarDir = L"down";
				}
			}

			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::O && gv->chatEnterText == false) // если отпустили кнопку Escape.
			{
				hideChat = !hideChat;
			}
			else if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::P && gv->chatEnterText == false)
			{
				//gv->autoScroll = !gv->autoScroll;
			}

			if (gv->event.type == sf::Event::TextEntered && gv->chatEnterText == true && hideChat == false)
			{
				if (gv->event.text.unicode == 8)
				{
					if (gv->userStr.size() > 0)
					{
						gv->userStr.resize(gv->userStr.size() - 1);
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
						if (!gv->userStr.empty())
						{
							if (gv->userStr[gv->userStr.size() - 1] == '\n')
							{
								gv->userStr.resize(gv->userStr.size() - 1);
								gv->numOfLinesInUserTextBox--;
							}
						}
					}
				}

				else if (gv->event.text.unicode == 13)
				{
					if (gv->userStr.size() > 0 && gv->userStr.size() <= 202 && gv->sendMsg == false && gv->recvMsg == false)
					{
						if (chat.trimString(gv->userStr, gv) == true)
						{
							gv->sendMsg = true;
						}
						else
						{
							gv->numOfLinesInUserTextBox = 1;
							chat.getUserText().clear();
							gv->userStr = L"";
						}
					}
				}
				else if (gv->event.text.unicode == 63)
				{
					if (gv->userStr.size() < 202)
					{
						chat.addNewLine(gv, chat);
						gv->userStr += L"\?";
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
					}
				}
				else if (gv->event.text.unicode == 34)
				{
					if (gv->userStr.size() < 202)
					{
						chat.addNewLine(gv, chat);
						gv->userStr += L"\"";
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
					}
				}
				else if (gv->event.text.unicode == 39)
				{
					if (gv->userStr.size() < 202)
					{
						chat.addNewLine(gv, chat);
						gv->userStr += L"\'";
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
					}
				}
				else if (gv->event.text.unicode == 92)
				{
					if (gv->userStr.size() < 202)
					{
						chat.addNewLine(gv, chat);
						gv->userStr += L"\\";
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
					}
				}

				else if (gv->event.text.unicode != 8 && gv->event.text.unicode != 27)
				{
					if (gv->userStr.size() < 202)
					{
						chat.addNewLine(gv, chat);
						gv->userStr += gv->event.text.unicode;
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->userStr;
					}
				}
			}
		}

		if (gv->scrollbarDir == L"up" && ((chat.getInnerScrollBar().getPosition().y - (chat.getInnerScrollBar().getSize().y / 2.f))) > chat.getOuterScrollBar().getPosition().y - (chat.getOuterScrollBar().getSize().y / 2.f)) // up
		{
			chat.moveUp(gv, chat);
			gv->scrollbarDir = L"";
		}

		else if (gv->scrollbarDir == L"down" && ((chat.getInnerScrollBar().getPosition().y + (chat.getInnerScrollBar().getSize().y / 2.f))) < chat.getOuterScrollBar().getPosition().y + (chat.getOuterScrollBar().getSize().y / 2.f)) // down
		{
			chat.moveDown(gv, chat);
			gv->scrollbarDir = L"";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gv->focusEvent == true && gv->chatEnterText == false)
		{
			movement = L"up";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gv->focusEvent == true && gv->chatEnterText == false)
		{
			movement = L"down";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gv->focusEvent == true && gv->chatEnterText == false)
		{
			movement = L"left";;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && gv->focusEvent == true && gv->chatEnterText == false)
		{
			movement = L"right";
		}

		gv->window.clear(gv->backgroundColor);

		for (auto& el : clientsVec)
		{
			gv->window.draw(el->playerShape);
			gv->window.draw(el->nickText);
		}

		if (hideChat == false)
		{
			gv->window.draw(chat.getOuterScrollBar());
			gv->window.draw(chat.getInnerScrollBar());
			gv->window.draw(chat.getChatTextBox());
			gv->window.draw(chat.getUserTextBox());
			gv->window.draw(chat.getUserText());
			gv->window.draw(chat.getChatText());
		}
		gv->window.display(); // отображаем в окне.
	}
}