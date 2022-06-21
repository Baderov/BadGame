#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include "Variables.h"

struct Clients
{
	std::string nickname = "";
	int id = 0;
};


sf::Packet& operator >> (sf::Packet& packet, std::vector<std::unique_ptr<Clients>>& clientsVec);

void connectToServer(GameVariables* gv);

void printOnlineClients();

void receive(GameVariables* gv);

void send(GameVariables* gv);

void startNetwork(GameVariables* gv);