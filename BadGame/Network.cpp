#include "Network.h"

HANDLE handle;
sf::TcpSocket sock; // ����������� ��������� ��� ����������� ������ ������� ����� ����������
sf::Packet packet; // ��� ������������� �������� �������� ������
std::string ip, nickname, prefix, msg, senderNickname;
int port;
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

void connectToServer()
{
	ip = "127.0.0.1";
	port = 2000;

	if (sock.connect(ip, port) == sf::Socket::Done) // ����������� � �������, ����� ������ ip � ����.
	{
		sf::Packet packet;
		prefix = "regNickname"; // regNickname - register a nickname.
		packet << prefix << nickname;
		sock.send(packet); // �������� ������
		SetConsoleTextAttribute(handle, 13);
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

void receive()
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
					getline(std::cin, nickname);
					SetConsoleTextAttribute(handle, 15);
					connectToServer();

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

void send()
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
				packet << prefix << nickname << msg; // ������ �������� ��������� � �����
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


void startNetwork()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, 14);
	std::cout << "You are a Client." << std::endl << std::endl;

	SetConsoleTextAttribute(handle, 11);
	std::cout << "Enter your nickname: ";
	getline(std::cin, nickname);
	SetConsoleTextAttribute(handle, 15);

	connectToServer();
	receive();

	std::thread receivethread([&]() { receive(); });
	receivethread.detach();

	send();
}