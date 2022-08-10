#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <iostream> // header that defines the standard input/output stream objects.
#include <thread> // header file for threads.
#include <windows.h> // windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API.
#include "Variables.h" // header file for global variables.
#include "Menu.h" // header file for working with the menu.
#include "Chat.h" // header file for working with chat.
#include "Entity.h"

struct Clients // structure for clients.
{
	Clients(int id, std::wstring nickname, sf::Vector2f pos); // first clients constructor.
	Clients(); // second clients constructor.
	int id; // client id.
	std::wstring nickname; // client nickname.
	sf::RectangleShape rectangleShape; // client shape.
	sf::Vector2f pos; // client position
	sf::Text nickText; // text for client nickname.
};

void addClientsToVector(GameVariables* gv); // function to add clients to the vector.

bool connectToServer(GameVariables* gv); // function to connect to the server.

void receiveData(GameVariables* gv); // function to receive data from the server.

void sendMessage(GameVariables* gv, sf::Packet& packet); // function to send message to the server.

void sendMoveRequest(GameVariables* gv, std::wstring side, sf::Packet& packet); // sending a move request to the server.

void sendPosition(GameVariables* gv, sf::Packet& packet); // function to send position to the server.

void sendData(GameVariables* gv); // function to send data to the server.

void startNetwork(GameVariables* gv); // function to start network.

void resetVariables(GameVariables* gv); // global variable reset function.

void multiplayerGame(GameVariables* gv, Entity*& player); // multiplayer game launch function.
