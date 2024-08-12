#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

#include "SingleplayerManager.h"
#include "NetworkManager.h"
#include "CustomWidget.h"
#include "Client.h"
#include "Bullet.h"

void connectedToServerRequest(std::unique_ptr<NetworkManager>& nm);

void regNickRequest(std::unique_ptr<NetworkManager>& nm);

void messageRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& msg);

void moveRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& currentClientStepPos);

void shootRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& creatorName, sf::Vector2f&& aimPos, sf::Vector2f&& bulletPos);

void mousePosRequest(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm);

void ghostRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& nickname, bool&& isGhost);

void sendClientRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void sendBulletRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);

#endif