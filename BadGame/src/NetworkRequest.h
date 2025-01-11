#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

#include "SingleplayerManager.h"
#include "NetworkManager.h"
#include "CustomWidget.h"
#include "Client.h"
#include "Bullet.h"

void respawnRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& nickname, sf::Vector2f&& startPos);

void connectedToServerRequest(std::unique_ptr<NetworkManager>& nm);

void regNickRequest(std::unique_ptr<NetworkManager>& nm);

void messageRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& msg);

void moveRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& currentClientStepPos);

void hitRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& woundedClientNick);

void shootRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& aimPos, sf::Vector2f&& bulletPos, sf::Vector2f&& currentVelocity);

void mousePosRequest(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm);

void ghostRequest(std::unique_ptr<NetworkManager>& nm, bool&& isGhost);

void sendClientRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

#endif