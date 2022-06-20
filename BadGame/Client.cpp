#include "Client.h"

// c_ - client.

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<c_Clients>>& clientsVec)
{
	for (auto& el : clientsVec)
	{
		packet >> el->id >> el->nickname;
	}
	return packet;
}

void connectToServer()
{
	c_ip = "127.0.0.1";
	c_port = 2000;

	if (c_sock.connect(c_ip, c_port) == sf::Socket::Done) // подключение к серверу, нужно ввести ip и порт.
	{
		sf::Packet packet;
		c_prefix = "regNickname"; // regNickname - register a nickname.
		packet << c_prefix << c_nickname;
		c_sock.send(packet); // отправка данных
		SetConsoleTextAttribute(c_handle, 13);
		return;
	}
	else
	{
		std::cout << "Connecting error. May be invalid ip or port, try again." << std::endl;
		connectToServer();
	}
}

void printOnlineClients()
{
	SetConsoleTextAttribute(c_handle, 11);
	std::cout << "\nOnline clients: \n";
	std::cout << "--------------------------------------------------------------------\n";
	for (int i = 0; i < c_clientsVec.size(); i++)
	{
		std::cout << "Client id: " + std::to_string(c_clientsVec[i]->id) + ". Client name: " + c_clientsVec[i]->nickname + ".\n";
	}
	std::cout << "--------------------------------------------------------------------\n\n";
	SetConsoleTextAttribute(c_handle, 15);
}

void receive()
{
	std::string msg;
	while (true)
	{
		if (c_sock.receive(c_packet) == sf::Socket::Done)
		{
			msg = "";

			if (c_packet >> c_prefix)
			{
				if (c_prefix == "conError" && c_packet >> msg)
				{
					SetConsoleTextAttribute(c_handle, 12);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(c_handle, 11);
					std::cout << "Enter your nickname: ";
					getline(std::cin, c_nickname);
					SetConsoleTextAttribute(c_handle, 15);
					connectToServer();

				}
				else if (c_prefix == "conSuccess" && c_packet >> msg)
				{
					SetConsoleTextAttribute(c_handle, 10);
					std::cout << "\n" + msg << std::endl;
					SetConsoleTextAttribute(c_handle, 15);
					break;
				}

				else if (c_prefix == "msg" && c_packet >> c_senderNickname && c_packet >> msg) // msg - message.
				{
					std::cout << c_senderNickname << ": " << msg << std::endl;
					c_packet.clear(); // чистим пакет
				}
				else if (c_prefix == "con" && c_packet >> msg) // con - connected.
				{
					SetConsoleTextAttribute(c_handle, 10);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(c_handle, 15);
				}
				else if (c_prefix == "discon" && c_packet >> msg) // discon - disconnected.
				{
					SetConsoleTextAttribute(c_handle, 12);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(c_handle, 15);
				}
				else if (c_prefix == "cmd" && c_packet >> c_clientsVecSize) // cmd - command.
				{
					c_clientsVec.clear();
					for (int i = 0; i < c_clientsVecSize; i++)
					{
						c_clientsVec.emplace_back(new c_Clients()); // создание пустых объектов вектора.
					}
					c_packet >> c_clientsVec >> msg;
					if (msg == "/online")
					{
						printOnlineClients();
					}
					c_packet.clear(); // чистим пакет
				}
				else
				{
					std::cout << "Reading error!" << std::endl;
					c_packet.clear(); // чистим пакет
				}
			}
		}
	}
}

void send()
{
	while (true)
	{
		c_packet.clear(); // чистим пакет
		c_msg = "";
		getline(std::cin, c_msg);
		if ((std::count(c_msg.begin(), c_msg.end(), '/') == 0))
		{
			if ((c_msg != "" && c_msg != " " && c_msg != "/online"))
			{
				c_prefix = "msg"; // msg - message.
				c_packet << c_prefix << c_nickname << c_msg; // пакуем значения координат в Пакет
				c_sock.send(c_packet); // отправка данных
			}
		}
		else if (c_msg == "/online")
		{
			c_prefix = "cmd"; // cmd - command.
			c_packet << c_prefix << c_msg; // пакуем значения координат в Пакет
			c_sock.send(c_packet); // отправка данных
		}
		else
		{
			std::cout << "*Command not found*" << std::endl;
		}
	}
}

void clientFunc()
{
	c_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(c_handle, 14);
	std::cout << "You are a Client." << std::endl << std::endl;

	SetConsoleTextAttribute(c_handle, 11);
	std::cout << "Enter your nickname: ";
	getline(std::cin, c_nickname);
	SetConsoleTextAttribute(c_handle, 15);

	connectToServer();
	receive();

	std::thread receivethread([&]() { receive(); });
	receivethread.detach();

	send();
}