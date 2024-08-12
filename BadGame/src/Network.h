#ifndef NETWORK_H
#define NETWORK_H

#include "Menu.h"
#include "Minimap.h" 
#include "SingleplayerManager.h"
#include "ClientRequest.h"
#include "ServerIsNotAvailable.h"
#include "CustomWidget.h"

enum class NetworkAction
{
	Nothing, ServerIsNotAvailable
}; inline NetworkAction networkAction;


void checkConnection(std::unique_ptr<NetworkManager>& nm);
void startNetwork(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm);

void addConnectedClientToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& joinedNick);
void addDisconnectedClientToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& leftNick);
void addMessageToChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, std::wstring&& senderNick, std::wstring&& msg);


void sendData(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw); // function to send data to the server.
void receiveData(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw); // function to receive data from the server.
void setMoveTarget(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void updateClients(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, Minimap& minimap);
void updateBullets(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);


void drawClients(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
void drawBullets(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
void drawWalls(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);


void multiplayerGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap);

#endif