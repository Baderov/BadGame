#pragma once
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <iostream> // header that defines the standard input/output stream objects.
#include "Variables.h"

class Clients // structure for clients.
{
private:
	sf::Int32 ping;
	std::wstring nickname; // client nickname.
	sf::Vector2f moveTargetPos, currentVelocity, stepPos;
	int id, HP;
	float maxSpeed, distance, width, height, DTMultiplier;
	bool isAlive, isMove, isShoot, isReload;
public:
	sf::Text nickText; // text for client nickname.
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape icon;
	sf::Clock pingClock;

	Clients(GameVariable* gv); // second clients constructor.
	void rotate(GameVariable* gv, sf::Vector2f& mousePos); // client rotate function.
	void updateLaser(GameVariable* gv); // laser update function.
	void update(GameVariable* gv);
	void moveToTarget(GameVariable* gv); // a function to move the sprite to the target.

	sf::Int32 getPing();
	std::wstring getNickname();
	sf::Vector2f getMoveTargetPos();
	sf::Vector2f getCurrentVelocity();
	sf::Vector2f getStepPos();
	int getId();
	int getHP();
	float getMaxSpeed();
	float getDistance();
	float getWidth();
	float getHeight();
	float getDTMultiplier();
	bool getIsAlive();
	bool getIsMove();
	bool getIsShoot();
	bool getIsReload();

	void setPing(sf::Int32 tempPing);
	void setNickname(std::wstring tempNick);
	void setMoveTargetPos(sf::Vector2f tempMoveTargetPos);
	void setCurrentVelocity(sf::Vector2f tempCurrentVelocity);
	void setStepPos(sf::Vector2f tempStepPos);
	void setPosition(sf::Vector2f& tempStepPos);
	void setId(int tempId);
	void setHP(int tempHP);
	void setMaxSpeed(float tempMaxSpeed);
	void setDistance(float tempDistance);
	void setWidth(float tempWidth);
	void setHeight(float tempHeight);
	void setDTMultiplier(float tempDTMultiplier);
	void setIsAlive(bool tempIsAlive);
	void setIsMove(bool tempIsMove);
	void setIsShoot(bool tempIsShoot);
	void setIsReload(bool tempIsReload);
	void setNickPosition();
};

sf::Vector2f getCurrentClientPos();
sf::Vector2f getCurrentClientMoveTargetPos();
sf::Vector2f getCurrentClientStepPos();
bool currentClientIsNullptr();
bool getCurrentClientIsMove();

void setCurrentClient(Clients* tempClient);
void setCurrentClientMoveTargetPos(sf::Vector2f tempMoveTargetPos);
void setCurrentClientIsMove(bool tempIsMove);
void setCurrentClientIsShoot(bool tempIsShoot);

void callMoveToTarget(GameVariable* gv);
void callUpdateLaser(GameVariable* gv);