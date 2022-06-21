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
	sf::RectangleShape playerShape;

};

bool connectToServer(GameVariables* gv);

void receive(GameVariables* gv);

void send(GameVariables* gv);

void sendPosition(GameVariables* gv);

void startNetwork(GameVariables* gv);

void multiplayerGame(GameVariables* gv);
