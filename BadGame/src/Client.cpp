#include "pch.h"
#include "Client.h"

Client::Client(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

void Client::init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, std::wstring name, sf::Vector2f startPos)
{
	isAlive = true;
	isMove = false;
	isReload = false;
	isGhost = false;
	isCollision = false;
	bulletHit = false;
	clientMoved = false;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	currentVelocity = sf::Vector2f(1.3f, 1.3f);
	moveTargetPos = this->startPos;
	maxSpeed = 5.f;
	reloadTime = 0.f;
	speed = 1000.f;
	stepPos = sf::Vector2f(0.f, 0.f);

	HP = 100;
	goldCoins = 0;
	maxHP = HP;
	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;
	playersListID = 0;

	ping = 0;
	pingClock.restart();
	distance = 0.f;

	texture.loadFromImage(gv->playerImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);
	sprite.setColor(sf::Color::White);

	collider.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	collider.setOrigin(collider.getSize().x / 2.f, collider.getSize().y / 2.f);
	collider.setPosition(this->startPos);
	collider.setFillColor(sf::Color::Magenta);

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
	icon.setPosition(this->startPos);
}


void Client::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isAlive)
	{
		if (HP <= 0)
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
			this->startPos = sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000));
			respawnRequest(nm, getName(), getStartPos());
			return;
		}

		if (bulletHit) { animateBulletHit(); }

		calcStepPos(gv, nm);

		if (isMove) { setClientMoved(true); }
	}
}

void Client::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	sprite.move(stepPos);
	icon.move(stepPos);
	collider.move(stepPos);
	setNameTextPos();
}

void Client::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (nm->getIsMinimapView()) { drawIcon(gw); }
	else
	{
		if (gv->getShowAimLaser() && gv->getFocusEvent()) { gw->window.draw(gv->aimLaser); }
		if (gv->getShowCollisionRect()) { drawCollider(gw); }
		else
		{
			drawNameText(gw);
			drawSprite(gw);
		}
	}
}

void Client::checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, clientsVec[i].get());
	}

	for (size_t i = 0; i < wallsVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, wallsVec[i].get());
	}
}

void Client::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Client::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}





// GETTERS
bool Client::getClientMoved()
{
	bool clientMoved = this->clientMoved;
	return clientMoved;
}

size_t Client::getPlayersListID()
{
	size_t playersListID = this->playersListID;
	return playersListID;
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


// SETTERS
void Client::setClientMoved(bool clientMoved)
{
	this->clientMoved = std::move(clientMoved);
}

void Client::setPlayersListID(size_t playersListID)
{
	this->playersListID = std::move(playersListID);
}

void Client::setPing(sf::Int32 ping)
{
	this->ping = std::move(ping);
}