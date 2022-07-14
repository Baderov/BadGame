#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include "Variables.h"
#include "Menu.h"
#include "Chat.h"

struct Clients
{
	int id;
	std::wstring nickname;
	sf::RectangleShape playerShape;
	sf::Vector2f pos;
	sf::Text nickText;
};

void fillClientsVector(GameVariables* gv);

bool connectToServer(GameVariables* gv);

void receive(GameVariables* gv, Chat& chat);

void send(GameVariables* gv);

void sendPosition(GameVariables* gv);

void startNetwork(GameVariables* gv, Chat& chat);

void multiplayerGame(GameVariables* gv, Entity*& player, Chat& chat);
