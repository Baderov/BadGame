#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Bullet::bulletID = 0;

void Bullet::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, sf::Vector2f aimPos, std::wstring creatorName)
{
	bulletID++;

	isAlive = true;
	allowToShoot = true;
	isMove = true;

	name = L"Bullet" + std::to_wstring(bulletID);
	this->aimPos = std::move(aimPos);
	this->creatorName = std::move(creatorName);
	this->startPos = std::move(startPos);

	maxSpeed = 60.f;
	HP = 10;

	currentVelocity = sf::Vector2f(0.3f, 0.3f);

	texture.loadFromImage(gv->bulletImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	collisionRect.setSize(sf::Vector2f(texture.getSize()));
	collisionRect.setOrigin(collisionRect.getSize().x / 2.f, collisionRect.getSize().y / 2.f);
	collisionRect.setPosition(this->startPos);
	collisionRect.setFillColor(sf::Color::Black);

	calcDirection();
}

void Bullet::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isAlive) { move(gv, gw, sm, nm); }
	else { returnToPool(gv, gw, sm, nm); }
}

void Bullet::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	moveToDirection();
	collisionRect.setPosition(sprite.getPosition());
	collision(gv, gw, sm, nm);
}

void Bullet::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getShowCollisionRect()) { drawCollisionRect(gw); }
	else { drawSprite(gw); }	
}

void Bullet::collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getIsSingleplayer())
	{
		for (size_t i = 0; i < wallsVec.size(); ++i)
		{
			collisionHandler(gv, nm, this, wallsVec[i].get());
		}

		for (size_t i = 0; i < boxesVec.size(); ++i)
		{
			collisionHandler(gv, nm, this, boxesVec[i].get());
		}

		for (size_t i = 0; i < enemiesVec.size(); ++i)
		{
			collisionHandler(gv, nm, this, enemiesVec[i].get());
		}

		collisionHandler(gv, nm, this, playerPtr.get());
	}

	else if (gv->getIsMultiplayer())
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
}

void Bullet::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < bulletsVec.size(); ++i)
	{
		if (bulletsVec[i]->getName() == name)
		{
			bulletsPool.returnToPool(bulletsVec, bulletsVec[i]);
			break;
		}
	}
}

void Bullet::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}

bool Bullet::getAllowToShoot()
{
	bool allowToShoot = this->allowToShoot;
	return allowToShoot;
}

void Bullet::setAllowToShoot(bool allowToShoot)
{
	this->allowToShoot = std::move(allowToShoot);
}