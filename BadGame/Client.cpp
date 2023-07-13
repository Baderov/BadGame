#include "pch.h"
#include "ObjectPool.hpp"
#include "Client.h"

Client::Client(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Client::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;
	isMove = false;
	isReload = false;

	allowToCollision = true;
	allowToMove = true;
	allowToSendMousePos = true;
	allowToSendMsg = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	texture.loadFromImage(gv->playerImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	rectHitbox.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
	rectHitbox.setPosition(this->startPos);

	currentVelocity = sf::Vector2f(0.85f, 0.85f);
	moveTargetPos = this->startPos;
	maxSpeed = 5.f;
	reloadTime = 0.f;

	HP = 100;
	goldCoins = 0;
	maxHP = HP;
	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;

	ping = 0;
	pingClock.restart();
	distance = 0.f;

	nameText.setFont(gv->consolasFont);
	nameText.setFillColor(sf::Color::Green);
	nameText.setCharacterSize(40);
	nameText.setOutlineThickness(2.f);
	nameText.setString(this->name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));
	nameText.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 80.f));

	icon.setRadius(static_cast<float>(gv->playerImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);
}

void Client::move(std::unique_ptr<GameVariable>& gv) {}

void Client::update(std::unique_ptr<GameVariable>& gv)
{
	if (isAlive)
	{
		rectHitbox.setPosition(sprite.getPosition());
		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Client::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

sf::Int32 Client::getPing()
{
	sf::Int32 ping = this->ping;
	return ping;
}

sf::Int32 Client::getPingClockElapsedTime()
{
	sf::Int32 elapsedTime = this->pingClock.restart().asMilliseconds();
	return elapsedTime;
}

bool Client::getAllowToMove()
{
	bool allowToMove = this->allowToMove;
	return allowToMove;
}
bool Client::getAllowToSendMsg()
{
	bool allowToSendMsg = this->allowToSendMsg;
	return allowToSendMsg;
}
bool Client::getAllowToSendMousePos()
{
	bool allowToSendMousePos = this->allowToSendMousePos;
	return allowToSendMousePos;
}

bool Client::getAllowToCollision()
{
	bool allowToCollision = this->allowToCollision;
	return allowToCollision;
}

void Client::setClientPosition(sf::Vector2f tempPos)
{
	sprite.setPosition(std::move(tempPos));
	icon.setPosition(std::move(tempPos));
}

void Client::moveClient(sf::Vector2f tempStepPos)
{
	sprite.move(std::move(tempStepPos));
	icon.move(std::move(tempStepPos));
}

void Client::setNickPosition()
{
	nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 80.f);
}

void Client::setPing(sf::Int32 ping)
{
	this->ping = std::move(ping);
}

void Client::setAllowToMove(bool allowToMove)
{
	this->allowToMove = std::move(allowToMove);
}
void Client::setAllowToSendMsg(bool allowToSendMsg)
{
	this->allowToSendMsg = std::move(allowToSendMsg);
}
void Client::setAllowToSendMousePos(bool allowToSendMousePos)
{
	this->allowToSendMousePos = std::move(allowToSendMousePos);
}
void Client::setAllowToCollision(bool allowToCollision)
{
	this->allowToCollision = std::move(allowToCollision);
}