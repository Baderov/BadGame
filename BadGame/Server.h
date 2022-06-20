#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <windows.h>

// s_ - server.

struct s_Clients
{
	s_Clients(sf::TcpSocket* socket)
	{
		this->socket = socket;
	}
	std::string nickname = "";
	int id = 0;
	sf::TcpSocket* socket = nullptr;
};

std::vector<s_Clients*> s_clientsVec; // Create a vector to store the future clients
sf::SocketSelector s_selector; // Create a selector
HANDLE s_handle;
std::string s_msg = "", s_nickname = "", s_prefix = "";
const int s_maxConnections = 1000;
int s_clientID = 0;

sf::Packet& operator << (sf::Packet& packet, std::vector<s_Clients*>& clientsVec);

void sendMsgToAllClients(sf::Packet& packet);

void printOnlineClients();

void sendListOfOnlineClients(sf::Packet& packet, s_Clients*& client);

void dataProcessing();

void serverFunc();

