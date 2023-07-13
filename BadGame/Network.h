#ifndef NETWORK_H
#define NETWORK_H

#include "Collision.h"
#include "ObjectPool.hpp"
#include "Menu.h"
#include "Client.h"
#include "Entity.h"
#include "PlayersList.h"
#include "Chat.h"
#include "Minimap.h" 
#include "Variables.h"
#include "ClientRequest.h"
#include "ServerIsNotAvailable.h"

void startNetwork(std::unique_ptr<GameVariable>& gv); // function to start network.


void sendData(std::unique_ptr<GameVariable>& gv, Chat& chat); // function to send data to the server.
void receiveData(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // function to receive data from the server.


void updateClients(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat);
void updateBullets(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat);
void gameUpdate(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat);


void minimapViewDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat);
void gameViewDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat);
void gameDraw(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // multiplayer game draw function.


void m_eventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // event handler for multiplayer.
void multiplayerGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // multiplayer game launch function.

#endif