#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

#include "Variables.h"
#include "Chat.h"

void connectToServerRequest(std::unique_ptr<GameVariable>& gv); // function to connect to the server.

void messageRequest(std::unique_ptr<GameVariable>& gv, Chat& chat); // function to send message to the server.

void moveRequest(std::unique_ptr<GameVariable>& gv, sf::Vector2f currentClientStepPos); // function to send a move request to the server.

void collisionRequest(std::unique_ptr<GameVariable>& gv, std::wstring entityName, sf::Vector2f entityPos);

void createBulletRequest(std::unique_ptr<GameVariable>& gv, std::wstring bulletName, std::wstring creatorName, sf::Vector2f aimPos, sf::Vector2f bulletPos);

void shootRequest(std::unique_ptr<GameVariable>& gv, std::wstring bulletName, sf::Vector2f bulletPos);

void mousePosRequest(std::unique_ptr<GameVariable>& gv); // function to send the mouse position to the server.

void sendClientRequests(std::unique_ptr<GameVariable>& gv, Chat& chat);

void sendBulletRequests(std::unique_ptr<GameVariable>& gv);

#endif
