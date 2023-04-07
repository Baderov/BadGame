#pragma once // used to provide additional control at compile time.
#include "Menu.h" // header file for working with the menu.
#include "Clients.h"
#include "Entity.h"
#include "PlayersList.h"
#include "Chat.h" // header file for working with chat.
#include "Minimap.h" // header file for minimap.

void createWalls(GameVariable* gv);

void serverIsNotAvailable(GameVariable* gv);

void connectToServer(GameVariable* gv); // function to connect to the server.

void startNetwork(GameVariable* gv); // function to start network.

bool checkConnection(GameVariable* gv); // function to check the connection between the client and the server.

void sendMessage(GameVariable* gv, Chat& chat); // function to send message to the server.

void sendMoveRequest(GameVariable* gv); // function to send a move request to the server.

void sendMousePos(GameVariable* gv); // function to send the mouse position to the server.

void m_enterMenu(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // menu entry function.

void m_eventHandler(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // event handling function for multiplayer.

void sendData(GameVariable* gv, Chat& chat); // function to send data to the server.

void receiveData(GameVariable* gv, PlayersList& playersList, Chat& chat); // function to receive data from the server.

void gameUpdate(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // multiplayer game update function.

void minimapViewDraw(GameVariable* gv, Minimap& minimap);

void gameViewDraw(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat);

void gameDraw(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // multiplayer game draw function.

void multiplayerGame(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // multiplayer game launch function.