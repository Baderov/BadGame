#include "pch.h"
#include "Client.h"

Client::Client(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

void Client::init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, std::wstring name, sf::Vector2f startPos, int HP)
{
	isAlive = true;
	isMove = false;
	isReload = false;
	isGhost = false;
	isCollision = false;
	bulletHit = false;
	moveReceived = false;
	sendMoveRequest = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);
	this->HP = std::move(HP);

	goldCoins = 0;
	maxHP = 100;
	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;
	playersListID = 0;
	numOfKills = 0;

	currentVelocity = sf::Vector2f(1.3f, 1.3f);
	moveTargetPos = this->startPos;
	maxSpeed = 5.f;
	reloadTime = 0.f;
	shootTime = 0.f;
	speed = 1000.f;
	stepPos = sf::Vector2f(0.f, 0.f);

	ping = 0;
	pingClock.restart();
	shootClock.restart();
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

	reloadRectOuter.setFillColor(grayColor);
	reloadRectOuter.setOutlineThickness(2.f);
	reloadRectOuter.setOutlineColor(sf::Color::Black);

	reloadRectInner.setFillColor(sf::Color::Black);
	reloadRectInner.setOutlineThickness(2.f);
	reloadRectInner.setOutlineColor(sf::Color::Black);

	reloadText.setFont(gv->consolasFont);
	reloadText.setCharacterSize(50);
	reloadText.setFillColor(sf::Color::Black);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);

	nameText.setFont(gv->consolasFont);
	nameText.setFillColor(sf::Color::Cyan);
	nameText.setCharacterSize(40);
	nameText.setOutlineThickness(2.f);
	nameText.setString(this->name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));
	nameText.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 110.f));

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
		if (getHP() <= 0)
		{
			setIsAlive(false);
			if (getName() == nm->getCurrentNickname()) { gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f)); }
			setStartPos(sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)));
			respawnRequest(nm, getName(), getStartPos());
			return;
		}

		if (getMoveReceived())
		{
			move(gv, gw, sm, nm);
			setMoveReceived(false);
		}

		if (getName() == nm->getCurrentNickname())
		{
			gw->setGameViewCenter(getSpritePos());
			calcStepPos(gv, nm);
			if (getIsMove()) { setSendMoveRequest(true); }
			calculateAmmo();
			updateReload(gv);

			if (gv->getGameLanguage() == GameLanguage::English)
			{
				gv->ammoText.setString(L"Ammo: " + std::to_wstring(getCurrentAmmo()) + L"/" + std::to_wstring(getMaxAmmo()));
			}
			else if (gv->getGameLanguage() == GameLanguage::Russian)
			{
				gv->ammoText.setString(L"Патроны: " + std::to_wstring(getCurrentAmmo()) + L"/" + std::to_wstring(getMaxAmmo()));
			}
		}

		animateBulletHit();
		updateHP();
	}
}

void Client::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	sprite.setPosition(getNewPos());
	icon.setPosition(getNewPos());
	collider.setPosition(getNewPos());
	setNameTextPos();
}

void Client::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (nm->getIsMinimapView()) { drawIcon(gw); }
	else
	{
		if (gv->getShowCollisionRect()) { drawCollider(gw); }
		else { drawSprite(gw); }

		drawHP(gw);
		drawNameText(gw);
		drawReload(gw);
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
	setTargetPos(std::move(targetPos));
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
}

void Client::createBullet(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm,
	sf::Vector2f&& startPos, sf::Vector2f&& aimPos, std::wstring&& creatorName, sf::Vector2f&& currentVelocity)
{
	std::lock_guard<std::mutex> lock(bullets_mtx);
	if (!isReload && bulletsPool.getFromPool(bulletsVec))
	{
		currentAmmo--;
		bulletsVec.back()->init(gv, gw, sm, nm, startPos, aimPos, creatorName, currentVelocity);
	}
}


// GETTERS
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

sf::Vector2f Client::getNewPos()
{
	sf::Vector2f newPos = this->newPos;
	return newPos;
}

bool Client::getMoveReceived()
{
	bool moveReceived = this->moveReceived;
	return moveReceived;
}

bool Client::getSendMoveRequest()
{
	bool sendMoveRequest = this->sendMoveRequest;
	return sendMoveRequest;
}


// SETTERS
void Client::setPlayersListID(size_t playersListID)
{
	this->playersListID = std::move(playersListID);
}

void Client::setPing(sf::Int32 ping)
{
	this->ping = std::move(ping);
}

void Client::setNewPos(sf::Vector2f newPos)
{
	this->newPos = std::move(newPos);
}

void Client::setMoveReceived(bool moveReceived)
{
	this->moveReceived = std::move(moveReceived);
}

void Client::setSendMoveRequest(bool sendMoveRequest)
{
	this->sendMoveRequest = std::move(sendMoveRequest);
}