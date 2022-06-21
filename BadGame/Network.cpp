#include "Network.h"

HANDLE handle;
sf::TcpSocket sock; // ����������� ��������� ��� ����������� ������ ������� ����� ����������
sf::Packet packet; // ��� ������������� �������� �������� ������
std::string prefix, msg, senderNickname;
sf::Uint64 clientsVecSize = 0;

bool isConnected = false;

std::vector<std::unique_ptr<Clients>> clientsVec; // Create a vector to store the future clients

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec)
{
	for (auto& el : clientsVec)
	{
		packet >> el->id >> el->nickname;
	}
	return packet;
}

bool connectToServer(GameVariables *gv)
{
	//ip = "127.0.0.1";
	//port = 2000;

	if (sock.connect(gv->serverIP, gv->serverPort) == sf::Socket::Done) // ����������� � �������, ����� ������ ip � ����.
	{
		sf::Packet packet;
		prefix = "regNickname"; // regNickname - register a nickname.
		packet << prefix << gv->nickname;
		sock.send(packet); // �������� ������
		SetConsoleTextAttribute(handle, 13);
		return true;
	}
	else
	{
		return false;
		//std::cout << "Connecting error. May be invalid ip or port, try again." << std::endl;
		//connectToServer(gv);
	}
}

void printOnlineClients()
{
	SetConsoleTextAttribute(handle, 11);
	std::cout << "\nOnline clients: \n";
	std::cout << "--------------------------------------------------------------------\n";
	for (int i = 0; i < clientsVec.size(); i++)
	{
		std::cout << "Client id: " + std::to_string(clientsVec[i]->id) + ". Client name: " + clientsVec[i]->nickname + ".\n";
	}
	std::cout << "--------------------------------------------------------------------\n\n";
	SetConsoleTextAttribute(handle, 15);
}

void receive(GameVariables* gv)
{
	std::string msg;
	while (true)
	{
		if (sock.receive(packet) == sf::Socket::Done)
		{
			msg = "";

			if (packet >> prefix)
			{
				if (prefix == "conError" && packet >> msg)
				{
					SetConsoleTextAttribute(handle, 12);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(handle, 11);
					std::cout << "Enter your nickname: ";
					getline(std::cin, gv->nickname);
					SetConsoleTextAttribute(handle, 15);
					connectToServer(gv);

				}
				else if (prefix == "conSuccess" && packet >> msg)
				{
					SetConsoleTextAttribute(handle, 10);
					std::cout << "\n" + msg << std::endl;
					SetConsoleTextAttribute(handle, 15);
					break;
				}

				else if (prefix == "msg" && packet >> senderNickname && packet >> msg) // msg - message.
				{
					std::cout << senderNickname << ": " << msg << std::endl;
					packet.clear(); // ������ �����
				}
				else if (prefix == "con" && packet >> msg) // con - connected.
				{
					SetConsoleTextAttribute(handle, 10);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(handle, 15);
				}
				else if (prefix == "discon" && packet >> msg) // discon - disconnected.
				{
					SetConsoleTextAttribute(handle, 12);
					std::cout << msg << std::endl;
					SetConsoleTextAttribute(handle, 15);
				}
				else if (prefix == "cmd" && packet >> clientsVecSize) // cmd - command.
				{
					clientsVec.clear();
					for (int i = 0; i < clientsVecSize; i++)
					{
						clientsVec.emplace_back(new Clients()); // �������� ������ �������� �������.
					}
					packet >> clientsVec >> msg;
					if (msg == "/online")
					{
						printOnlineClients();
					}
					packet.clear(); // ������ �����
				}
				else
				{
					std::cout << "Reading error!" << std::endl;
					packet.clear(); // ������ �����
				}
			}
		}
	}
}

void send(GameVariables* gv)
{
	while (true)
	{
		packet.clear(); // ������ �����
		msg = "";
		getline(std::cin, msg);
		if ((std::count(msg.begin(), msg.end(), '/') == 0))
		{
			if ((msg != "" && msg != " " && msg != "/online"))
			{
				prefix = "msg"; // msg - message.
				packet << prefix << gv->nickname << msg; // ������ �������� ��������� � �����
				sock.send(packet); // �������� ������
			}
		}
		else if (msg == "/online")
		{
			prefix = "cmd"; // cmd - command.
			packet << prefix << msg; // ������ �������� ��������� � �����
			sock.send(packet); // �������� ������
		}
		else
		{
			std::cout << "*Command not found*" << std::endl;
		}
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
			el->getSprite().setFillColor(sf::Color::White); // �������� ������ ������.
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
			el->getSprite().setFillColor(sf::Color::White); // �������� ������ ������.
		}
		gv->isMultiplayerGame = false;
	}


	//std::thread receivethread([&]() { receive(gv); });
	//receivethread.detach();

	//send(gv);
}


void multiplayerGame(GameVariables* gv)
{
	while (gv->window.isOpen()) // ���� ���� �������.
	{
		//gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // �������� ������ ����.

		while (gv->window.pollEvent(gv->event)) // ���� ���������� �������.
		{
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); } // ���� ��������� ������� ������� �������� "�������" - ���� �����������.
		}
		gv->window.clear(sf::Color::White); // ������� ���� ������ ������.
		gv->window.display(); // ���������� � ����.
	}
}