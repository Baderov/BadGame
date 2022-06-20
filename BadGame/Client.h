#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>

// c_ - client.

struct c_Clients
{
	std::string nickname = "";
	int id = 0;
};

std::vector<std::unique_ptr<c_Clients>> c_clientsVec; // Create a vector to store the future clients

HANDLE c_handle;
sf::TcpSocket c_sock; // программный интерфейс для обеспечения обмена данными между процессами
sf::Packet c_packet; // для осуществления пакетной передачи дынных
std::string c_ip, c_nickname, c_prefix, c_msg, c_senderNickname;
int c_port;
sf::Uint64 c_clientsVecSize = 0;
bool c_isConnected = false;

sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<c_Clients>>& clientsVec);

void connectToServer();

void printOnlineClients();

void receive();

void send();

void clientFunc();