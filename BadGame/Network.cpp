#include "Network.h"

//ip - "127.0.0.1";
//port - 2000;

HANDLE handle;
sf::TcpSocket sock; // программный интерфейс для обеспечения обмена данными между процессами
std::string senderNickname;
sf::Uint64 clientsVecSize = 0;

bool isConnected = false;
bool allowMove = false;

std::vector<std::unique_ptr<Clients>> clientsVec; // Create a vector to store the future clients

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec)
{
	for (auto& el : clientsVec)
	{
		packet >> el->id >> el->nickname;
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
					if (packet >> msg)
					{
						SetConsoleTextAttribute(handle, 12);
						std::cout << msg << std::endl;
						SetConsoleTextAttribute(handle, 15);
					}
				}
				else if (prefix == "move")
				{
					if (packet >> allowMove && packet >> side)
					{
						if (side == "up" && allowMove == true)
						{
							gv->playerShape.move(0.f, -5.f);
						}
						else if (side == "down" && allowMove == true)
						{
							gv->playerShape.move(0.f, 5.f);
						}
						else if (side == "left" && allowMove == true)
						{
							gv->playerShape.move(-5.f, 0.f);
						}
						else if (side == "right" && allowMove == true)
						{
							gv->playerShape.move(5.f, 0.f);
						}
					}			
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
	sf::Vector2f pos = gv->playerShape.getPosition();
	packet << prefix << gv->nickname << pos.x << pos.y;
	sock.send(packet);
}

void moveRequest(GameVariables* gv, std::string side)
{
	sf::Packet packet; // для осуществления пакетной передачи данных
	packet.clear(); // чистим пакет
	std::string prefix = "move";
	packet << prefix << side;
	sock.send(packet);
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
	gv->playerShape.setSize(sf::Vector2f(100.f, 100.f));
	gv->playerShape.setFillColor(sf::Color::Black);
	gv->playerShape.setOrigin(gv->playerShape.getSize() / 2.f);
	gv->playerShape.setPosition(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f);


	std::thread receiveThread([&]() { receive(gv); });
	receiveThread.detach();

	//std::thread sendThread([&]() { send(gv); });
	//sendThread.detach();


	while (gv->window.isOpen()) // пока меню открыто.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); } // если состояние события приняло значение "Закрыто" - окно закрывается.
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sendPosition(gv);
			moveRequest(gv, "up");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sendPosition(gv);
			moveRequest(gv, "down");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sendPosition(gv);
			moveRequest(gv, "left");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sendPosition(gv);
			moveRequest(gv, "right");
		}
		gv->window.clear(sf::Color::White); // очищаем окно черным цветом.
		gv->window.draw(gv->playerShape);
		gv->window.display(); // отображаем в окне.
	}
}