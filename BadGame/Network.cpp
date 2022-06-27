#include "Network.h"

//ip - "127.0.0.1";
//port - 2000;

HANDLE handle;
sf::TcpSocket sock; // программный интерфейс для обеспечения обмена данными между процессами
std::string senderNickname;
sf::Uint64 clientsVecSize = 0;

bool isConnected = false;
bool allowMove = false;
bool isVectorReceived = false;

std::vector<std::unique_ptr<Clients>> clientsVec; // Create a vector to store the future clients

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
	if (sock.connect(gv->serverIP, gv->serverPort) == sf::Socket::Done) // подключение к серверу, нужно ввести ip и порт.
	{
		sf::Packet packet;
		std::string prefix = "regNickname"; // regNickname - register a nickname.
		packet << prefix << gv->nickname;
		sock.send(packet); // отправка данных
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
	std::string prefix = "", msg = "", side = "";
	while (true)
	{
		if (sock.receive(packet) == sf::Socket::Done)
		{
			msg = "";
			prefix = "";
			if (packet >> prefix)
			{
				if (prefix == "conError")
				{
					if (packet >> msg)
					{
						SetConsoleTextAttribute(handle, 12);
						std::cout << msg << std::endl;
						SetConsoleTextAttribute(handle, 11);
						std::cout << "Enter your nickname: ";
						getline(std::cin, gv->nickname);
						SetConsoleTextAttribute(handle, 15);
						connectToServer(gv);
					}
				}
				else if (prefix == "conSuccess")
				{
					if (packet >> msg)
					{
						SetConsoleTextAttribute(handle, 10);
						std::cout << "\n" + msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
						break;
					}
				}
				else if (prefix == "con") // con - connected.
				{
					if (packet >> msg)
					{
						SetConsoleTextAttribute(handle, 10);
						std::cout << msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
					}
				}
				else if (prefix == "discon") // discon - disconnected.
				{
					std::string disconnectedNick = "";
					if (packet >> msg && packet >> disconnectedNick)
					{
						SetConsoleTextAttribute(handle, 12);
						std::cout << msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
						clientsVec.erase(std::remove_if(clientsVec.begin(), clientsVec.end(), [&](std::unique_ptr<Clients>& client) { return client.get()->nickname == disconnectedNick; }), clientsVec.end());
					}
				}
				else if (prefix == "move")
				{
					std::string tempNick = "";
					if (packet >> allowMove && packet >> side && packet >> tempNick)
					{
						for (auto& el : clientsVec)
						{
							if (el->nickname == tempNick && allowMove == true)
							{
								if (side == "up")
								{
									el->playerShape.move(0.f, -5.f);
								}
								else if (side == "down")
								{
									el->playerShape.move(0.f, 5.f);
								}
								else if (side == "left")
								{
									el->playerShape.move(-5.f, 0.f);
								}
								else if (side == "right")
								{
									el->playerShape.move(5.f, 0.f);
								}
								el->nickText.setPosition(el->playerShape.getPosition().x, el->playerShape.getPosition().y - 80.f);
							}
						}				
					}			
				}

				else if (prefix == "pos")
				{
					std::string tempNick = "";
					sf::Vector2f tempPos;
					if (packet << tempNick && packet << tempPos.x && packet << tempPos.y)
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

				else if (prefix == "clientsList")
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



void send(GameVariables* gv)
{
	while (true)
	{
		//sendPosition(gv);
	}
}

void sendPosition(GameVariables* gv)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::string prefix = "pos";
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
	sock.send(packet);
}

void moveRequest(GameVariables* gv, std::string side)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::string prefix = "move";
	packet << prefix << side << gv->nickname;
	sock.send(packet);
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
			el->playerShape.setPosition(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f);

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
	if (connectToServer(gv) == true)
	{
		std::cout << "connect true!" << std::endl;
		gv->drawErrorLabel = false;
		gv->allowButtons = true;
		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}
		receive(gv);
		gv->isMultiplayerGame = true;
	}

	else
	{
		std::cout << "connect false!" << std::endl;
		gv->drawErrorLabel = true;
		gv->allowButtons = true;
		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}
		gv->isMultiplayerGame = false;
	}
}

void multiplayerGame(GameVariables* gv)
{

	std::thread receiveThread([&]() { receive(gv); });
	receiveThread.detach();

	//std::thread sendThread([&]() { send(gv); });
	//sendThread.detach();


	while (gv->window.isOpen()) // пока меню открыто.
	{
		fillClientsVector(gv);
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::LostFocus)
			{
				gv->focus = false;
			}
			else if (gv->event.type == sf::Event::GainedFocus)
			{
				gv->focus = true;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); } // если состояние события приняло значение "Закрыто" - окно закрывается.
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gv->focus == true)
		{
			sendPosition(gv);
			moveRequest(gv, "up");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gv->focus == true)
		{
			sendPosition(gv);
			moveRequest(gv, "down");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gv->focus == true)
		{
			sendPosition(gv);
			moveRequest(gv, "left");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && gv->focus == true)
		{
			sendPosition(gv);
			moveRequest(gv, "right");
		}
		gv->window.clear(sf::Color::White); // очищаем окно черным цветом.
		for (auto& el : clientsVec)
		{
			gv->window.draw(el->playerShape);
			gv->window.draw(el->nickText);
		}
		gv->window.display(); // отображаем в окне.
	}
}