#include "Server.h"

// s_ - server.



sf::Packet& operator << (sf::Packet& packet, std::vector<s_Clients*>& clientsVec)
{
	for (auto& el : clientsVec)
	{
		packet << el->id << el->nickname;
	}
	return packet;
}

void sendMsgToAllClients(sf::Packet& packet)
{
	for (auto& clnt : s_clientsVec)
	{
		clnt->socket->send(packet);
	}
}

void printOnlineClients()
{
	SetConsoleTextAttribute(s_handle, 11);
	std::cout << "\nOnline clients: \n";
	std::cout << "--------------------------------------------------------------------\n";
	if (s_clientsVec.size() > 0)
	{
		for (int i = 0; i < s_clientsVec.size(); i++)
		{
			std::cout << "Client id: " + std::to_string(s_clientsVec[i]->id) + ". Client name: " + s_clientsVec[i]->nickname + ".\n";
		}
	}
	else
	{
		SetConsoleTextAttribute(s_handle, 14);
		std::cout << "***Server is empty!***\n";
		SetConsoleTextAttribute(s_handle, 15);
	}

	std::cout << "--------------------------------------------------------------------\n\n";
	SetConsoleTextAttribute(s_handle, 15);
}

void sendListOfOnlineClients(sf::Packet& packet, s_Clients*& client)
{
	s_prefix = "cmd";
	packet.clear(); // чистим пакет

	packet << s_prefix << s_clientsVec.size() << s_clientsVec << s_msg;
	client->socket->send(packet);

	packet.clear(); // чистим пакет
	s_prefix = ""; s_msg = "";
}

void dataProcessing()
{
	for (auto& client : s_clientsVec)
	{
		if (s_selector.isReady(*client->socket))
		{
			// The client has sent some data, we can receive it
			sf::Packet packet;
			if (client->socket->receive(packet) == sf::Socket::Done) // если пользователь онлайн и отправил данные.
			{
				if (packet >> s_prefix)
				{
					if (s_prefix == "regNickname" && packet >> s_nickname)
					{
						packet.clear(); // чистим пакет
						client->id = s_clientsVec.size() - 1;
						client->nickname = s_nickname;

						s_prefix = "con";
						std::string connectedMsg = client->nickname + " connected!";
						SetConsoleTextAttribute(s_handle, 10);
						std::cout << connectedMsg << std::endl;
						SetConsoleTextAttribute(s_handle, 15);

						packet << s_prefix << connectedMsg;
						sendMsgToAllClients(packet);

						printOnlineClients();
						s_prefix = ""; s_nickname = "";
					}
					else if (s_prefix == "msg" && packet >> s_nickname && packet >> s_msg)
					{
						sendMsgToAllClients(packet);
						packet.clear(); // чистим пакет
						s_prefix = ""; s_msg = "";
					}
					else if (s_prefix == "cmd" && packet >> s_msg && s_msg == "/online")
					{
						sendListOfOnlineClients(packet, client);
					}
				}
				else
				{
					std::cout << "Reading error: " << std::endl;
					packet.clear(); // чистим пакет
				}
			}

			else if (client->socket->receive(packet) == sf::Socket::Disconnected) // если пользователь отключилс€.
			{
				std::string disconnectedMsg = client->nickname + " disconnected!";
				SetConsoleTextAttribute(s_handle, 12);
				std::cout << disconnectedMsg << std::endl;
				//std::cout << "vecSize before: " << clientsVec.size() << std::endl;

				s_selector.remove(*client->socket);
				client->socket->disconnect();

				auto it = std::remove(s_clientsVec.begin(), s_clientsVec.end(), client);
				s_clientsVec.erase(it, s_clientsVec.end());

				//std::cout << "vecSize after: " << clientsVec.size() << std::endl;
				printOnlineClients();

				packet.clear();
				s_prefix = "discon";

				packet << s_prefix << disconnectedMsg;
				sendMsgToAllClients(packet);
			}
		}
	}
}

void serverFunc()
{
	s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(s_handle, 14);
	std::cout << "You are a Server." << std::endl << std::endl;
	int port = 2000;
	// Create a socket to listen to new connections
	sf::TcpListener listener;
	listener.listen(port);


	// Add the listener to the selector
	s_selector.add(listener);
	// Endless loop that waits for new connections
	while (true)
	{
		// Make the selector wait for data on any socket
		if (s_selector.wait())
		{
			// Test the listener
			if (s_selector.isReady(listener))
			{
				// The listener is ready: there is a pending connection

				sf::TcpSocket* client = new sf::TcpSocket;
				std::string msg = "";
				if (listener.accept(*client) == sf::Socket::Done)
				{
					sf::Packet packet;
					bool isConnected = true; // ошибка подключени€
					if (client->receive(packet) == sf::Socket::Done) // если пользователь онлайн и отправил данные.
					{
						if (packet >> s_prefix && packet >> s_nickname && s_prefix == "regNickname")
						{
							for (auto& el : s_clientsVec)
							{
								if (s_nickname == el->nickname)
								{
									isConnected = false;
									packet.clear();
									msg = "Nickname already taken!";
									s_prefix = "conError";
									packet << s_prefix << msg << isConnected;
									client->send(packet);
									client->disconnect();
									break;
								}
							}
							if (isConnected == true)
							{
								packet.clear();
								msg = "Welcome to the club, buddy";
								s_prefix = "conSuccess";
								packet << s_prefix << msg << isConnected;
								client->send(packet);

								// Add the new client to the clients list
								s_clientsVec.push_back(new s_Clients(client)); // <------ ¬ќ«ћќ∆Ќјя ”“≈„ ј!
								s_clientsVec.back()->id = s_clientID;
								s_clientsVec.back()->nickname = s_nickname;
								s_clientID++;

								s_prefix = "con";
								std::string connectedMsg = s_clientsVec.back()->nickname + " connected!";
								SetConsoleTextAttribute(s_handle, 10);
								std::cout << connectedMsg << std::endl;
								SetConsoleTextAttribute(s_handle, 15);
								packet.clear(); // чистим пакет
								packet << s_prefix << connectedMsg;
								sendMsgToAllClients(packet);


								s_prefix = "cmd";
								sf::Uint64 clientsVecSize = s_clientsVec.size();
								msg = "/online";
								packet.clear(); // чистим пакет
								packet << s_prefix << clientsVecSize << s_clientsVec << msg;
								client->send(packet);


								packet.clear(); // чистим пакет
								s_prefix = ""; msg = "";

								printOnlineClients();
							}
						}
					}


					// Add the new client to the selector so that we will
					// be notified when he sends something
					s_selector.add(*client);

					//sendListOfOnlineClients(pckt, clientsVec.back());
				}
				else
				{
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				dataProcessing();
			}
		}
	}
}