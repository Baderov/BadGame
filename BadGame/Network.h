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
#include <mutex>

struct Clients
{
	Clients(int id, std::wstring nickname, sf::Vector2f pos);
	Clients();
	int id;
	std::wstring nickname;
	sf::RectangleShape playerShape;
	sf::Vector2f pos;
	sf::Text nickText;
};

void fillClientsVector(GameVariables* gv);

bool connectToServer(GameVariables* gv);

void receive(GameVariables* gv);

void send(GameVariables* gv);

void sendPosition(GameVariables* gv);

void startNetwork(GameVariables* gv);

void updateVariables(GameVariables* gv);

void multiplayerGame(GameVariables* gv, Entity*& player);
