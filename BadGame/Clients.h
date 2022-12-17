#pragma once
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <iostream> // header that defines the standard input/output stream objects.
#include "Variables.h"

struct Clients // structure for clients.
{
	Clients(GameVariable* gv); // second clients constructor.
	void rotate(GameVariable* gv, sf::Vector2f& mousePos); // client rotate function.
	void updateLaser(GameVariable* gv); // laser update function.
	void update(GameVariable* gv);
	void moveToTarget(GameVariable* gv); // a function to move the sprite to the target.

	void setClientPing(sf::Int32 tempPing);
	sf::Int32 getClientPing();

	std::wstring nickname; // client nickname.
	sf::Text nickText; // text for client nickname.
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f moveTargetPos, currentVelocity, stepPos;

	sf::Clock pingClock;
	int id, HP;
	float maxSpeed, distance, w, h, DTMultiplier;
	bool isAlive, isMove, isShoot, isReload;

private:
	sf::Int32 ping;
};

sf::Vector2f getClientPos();
sf::Vector2f getMoveTargetPos();
sf::Vector2f getClientStepPos();
bool clientIsNullptr();
bool getClientIsMove();
void callMoveToTarget(GameVariable* gv);
void callUpdateLaser(GameVariable* gv);
void setCurrentClient(Clients* tempClient);
void setMoveTargetPos(sf::Vector2f tempMoveTargetPos);
void setIsMove(bool tempIsMove);
void setIsShoot(bool tempIsShoot);