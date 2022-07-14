#include "Network.h"

//ip - "127.0.0.1";
//port - 2000;

HANDLE handle;

std::wstring senderNickname;
sf::Uint64 clientsVecSize = 0;

bool isConnected = false;
bool allowMove = false;
bool isVectorReceived = false;
bool isNickTaken = false;
bool hideChat = false;
bool sendMsg = false;
std::wstring movement = L"";

std::vector<std::unique_ptr<Clients>> clientsVec; // вектор структур для клиентов.

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

void receive(GameVariables* gv, Chat& chat)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	std::wstring prefix = L"", msg = L"", side = L"";
	while (true)
	{
		if (gv->funcTerminate == true)
		{
			gv->funcTerminate = false;
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
					break;
				}
				else if (prefix == L"conSuccess")
				{
					isNickTaken = false;
					break;
				}
				else if (prefix == L"con") // con - connected.
				{
					if (packet >> msg)
					{
						SetConsoleTextAttribute(handle, 10);
						std::wcout << msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
					}
				}
				else if (prefix == L"discon") // discon - disconnected.
				{
					std::wstring disconnectedNick = L"";
					if (packet >> msg && packet >> disconnectedNick)
					{
						SetConsoleTextAttribute(handle, 12);
						std::wcout << msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
						clientsVec.erase(std::remove_if(clientsVec.begin(), clientsVec.end(), [&](std::unique_ptr<Clients>& client) { return client.get()->nickname == disconnectedNick; }), clientsVec.end());
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
					std::wstring tempNick = L"";
					if (packet >> tempNick && packet >> gv->chatStr)
					{
						gv->chatPrefix = tempNick + L": ";
						addString(gv, chat);
						gv->numOfLinesInChat = 1;
						chat.getUserText().clear();
						gv->chatStr = L"";		
						gv->permissionToSend = true;
						chat.getUserTextBox().setFillColor(sf::Color::White);
					}
				}

				else if (prefix == L"clientsList")
				{
					if (packet >> clientsVecSize)
					{
						clientsVec.clear();
						for (int i = 0; i < clientsVecSize; i++)
						{
							clientsVec.emplace_back(new Clients()); // создание пустых объектов вектора.
						}

						if (packet >> clientsVec)
						{
							isVectorReceived = true;
						}
						else
						{
							isVectorReceived = false;
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
	packet << prefix << gv->nickname << gv->chatStr;
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
		if (gv->funcTerminate == true)
		{
			gv->funcTerminate = false;
			break;
		}
		if (sendMsg == true)
		{
			sendMsg = false;
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

void startNetwork(GameVariables* gv, Chat& chat)
{
	if (connectToServer(gv) == true)
	{
		gv->allowButtons = true;
		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}
		receive(gv, chat);
		if (isNickTaken == true)
		{
			gv->menuError = MenuErrors::NicknameIsAlreadyTaken;
			gv->multiPlayerGame = false;
		}
		else if (isNickTaken == false)
		{
			gv->menuError = MenuErrors::NoErrors;
			gv->multiPlayerGame = true;
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
}

void multiplayerGame(GameVariables* gv, Entity*& player, Chat& chat)
{
	std::thread receiveThread([&]() { receive(gv, chat); });
	receiveThread.detach();

	std::thread sendThread([&]() { send(gv); });
	sendThread.detach();

	while (gv->window.isOpen()) // пока меню открыто.
	{
		fillClientsVector(gv);
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0;

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
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); } // если состояние события приняло значение "Закрыто" - окно закрывается.

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
					chat.getUserTextBox().setFillColor(sf::Color(255, 255, 255, 180));
				}
				else if (gv->menuNum == 1)
				{
					gv->chatEnterText = true;
					chat.getUserTextBox().setFillColor(sf::Color::White);
				}
			}

			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				menuEventHandler(gv, player, chat);
				if (gv->multiPlayerGame == false) { gv->exitFromMenu = true; gv->funcTerminate = true; return; }
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

			if (gv->event.type == sf::Event::TextEntered && gv->chatEnterText == true && hideChat == false)
			{
				if (gv->event.text.unicode == 8)
				{
					if (gv->chatStr.size() > 0)
					{
						gv->chatStr.resize(gv->chatStr.size() - 1);
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->chatStr;
						if (!gv->chatStr.empty())
						{
							if (gv->chatStr[gv->chatStr.size() - 1] == '\n')
							{
								gv->chatStr.resize(gv->chatStr.size() - 1);
								gv->numOfLinesInChat--;
							}
						}
					}
				}

				else if (gv->event.text.unicode == 13)
				{
					if (gv->chatStr.size() > 0 && gv->chatStr.size() <= 202 && gv->permissionToSend == true)
					{
						sendMsg = true;
						gv->permissionToSend = false;
						chat.getUserTextBox().setFillColor(sf::Color::Red);
					}
				}
				
				else if (gv->event.text.unicode != 27)
				{
					if (gv->chatStr.size() < 202)
					{
						if (gv->chatStr.size() == 54 || gv->chatStr.size() == 109 || gv->chatStr.size() == 164)
						{
							gv->chatStr += '\n';
							chat.getUserText().clear();
							chat.getUserText() << sf::Color::Black << gv->chatStr;
							gv->numOfLinesInChat++;
						}
						gv->chatStr += gv->event.text.unicode;
						chat.getUserText().clear();
						chat.getUserText() << sf::Color::Black << gv->chatStr;
					}
				}
			}
		}

		if (gv->scrollbarDir == L"up" && ((chat.getInnerScrollBar().getPosition().y - (chat.getInnerScrollBar().getSize().y / 2.f))) > chat.getOuterScrollBar().getPosition().y - (chat.getOuterScrollBar().getSize().y / 2.f)) // up
		{
			moveUp(gv, chat);
			gv->scrollbarDir = L"";
		}

		else if (gv->scrollbarDir == L"down" && ((chat.getInnerScrollBar().getPosition().y + (chat.getInnerScrollBar().getSize().y / 2.f))) < chat.getOuterScrollBar().getPosition().y + (chat.getOuterScrollBar().getSize().y / 2.f)) // down
		{
			moveDown(gv, chat);
			gv->scrollbarDir = L"";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gv->focusEvent == true && gv->chatEnterText ==false)
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
			gv->window.draw(chat.getChatTextBox());
			gv->window.draw(chat.getUserTextBox());
			gv->window.draw(chat.getOuterScrollBar());
			gv->window.draw(chat.getInnerScrollBar());
			gv->window.draw(chat.getUserText());
			gv->window.draw(chat.getChatText());
		}
		gv->window.display(); // отображаем в окне.
	}
}