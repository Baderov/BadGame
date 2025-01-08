#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Bullet::bulletID = 0;

void Bullet::init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, sf::Vector2f startPos, sf::Vector2f aimPos, std::wstring creatorName)
{
	bulletID++;

	isAlive = true;
	isMove = true;
	allowToShoot = true;

	name = L"Bullet" + std::to_wstring(bulletID);
	this->aimPos = std::move(aimPos);
	this->creatorName = std::move(creatorName);
	this->startPos = std::move(startPos);

	maxSpeed = 1000.f;
	currentVelocity = sf::Vector2f(0.f, 0.f);
	HP = 10;

	texture.loadFromImage(gv->bulletImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	collider.setSize(sf::Vector2f(texture.getSize()));
	collider.setOrigin(collider.getSize().x / 2.f, collider.getSize().y / 2.f);
	collider.setPosition(this->startPos);
	collider.setFillColor(sf::Color::Black);

	calcDirection(gv->getDT());
}

void Bullet::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	move(gv, gw, sm, nm);
}

void Bullet::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < 10; i++)
	{
		moveToDirection();
		checkCollision(gv, gw, sm, nm);
		if (!isAlive) { returnToPool(gv, gw, sm, nm); return; }
	}
}

void Bullet::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getShowCollisionRect()) { drawCollider(gw); }
	else { drawSprite(gw); }
}

void Bullet::checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
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

void Bullet::calcDirection(float&& deltaTime)
{
	aimDir = aimPos - sprite.getPosition(); // distance from the mouse to the current position of the sprite.
	aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x) + (aimDir.y * aimDir.y)); // direction.
	currentVelocity = aimDirNorm * maxSpeed * deltaTime; // vector speed = direction * linear speed * delta time.
}

bool Bullet::getAllowToShoot()
{
	bool allowToShoot = this->allowToShoot;
	return allowToShoot;
}

void Bullet::setAllowToShoot(bool allowToShoot)
{
	this->allowToShoot = std::move(allowToShoot);
}