#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <iostream> // header that defines the standard input/output stream objects.
#include <thread> // header file for threads.
#include <windows.h> // windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API.
#include "Variables.h" // header file for global variables.
#include "Menu.h" // header file for working with the menu.
#include "Chat.h" // header file for working with chat.
#include "Clients.h"
#include "Entity.h"
#include "PlayersList.h"

void setSocketBlocking(bool blocking); // socket blocking function.

void enterMenu(GameVariable* gv, Entity*& player); // menu entry function.

void connectToServer(GameVariable* gv); // function to connect to the server.

void startNetwork(GameVariable* gv); // function to start network.

bool checkConnection(GameVariable* gv); // function to check the connection between the client and the server.

void sendMessage(GameVariable* gv); // function to send message to the server.

void sendMoveRequest(GameVariable* gv); // function to send a move request to the server.

void sendMousePos(GameVariable* gv); // function to send the mouse position to the server.

void resetVariables(GameVariable* gv); // global variable reset function.

void eventHandler(GameVariable* gv, Chat& chat, Entity*& player); // event handling function.

void sendData(GameVariable* gv); // function to send data to the server.

void receiveData(GameVariable* gv); // function to receive data from the server.

void setWindowView(GameVariable* gv); // function to set window view.

void gameUpdate(GameVariable* gv, Chat& chat, Entity*& player); // multiplayer game update function.

void gameDraw(GameVariable* gv, Chat& chat); // multiplayer game draw function.

void multiplayerGame(GameVariable* gv, Entity*& player); // multiplayer game launch function.