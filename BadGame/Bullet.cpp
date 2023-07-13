#include "pch.h"
#include "ObjectPool.hpp"
#include "Bullet.h" // header file for bullets.

Bullet::Bullet(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Bullet::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, sf::Vector2f aimPos, std::wstring name, std::wstring creatorName)
{
	isAlive = true;
	allowToShoot = true;
	isMove = true;

	this->name = std::move(name);
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

	rectHitbox.setSize(sf::Vector2f(texture.getSize()));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
	rectHitbox.setPosition(this->startPos);
	rectHitbox.setFillColor(sf::Color::Magenta);

	calcDirection();
}

void Bullet::update(std::unique_ptr<GameVariable>& gv)
{
	if (isAlive) // if bullet is alive, then:
	{
		move(gv);
		if (gv->getIsMultiplayer() && (sprite.getPosition().x <= 0.f || sprite.getPosition().y <= 0.f || sprite.getPosition().x >= 5000.f || sprite.getPosition().y >= 5000.f)) { isAlive = false; }
	}
}

void Bullet::move(std::unique_ptr<GameVariable>& gv) { moveToDirection(); rectHitbox.setPosition(sprite.getPosition()); }

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