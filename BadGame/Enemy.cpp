#include "pch.h"
#include "Enemy.h" 

Enemy::Enemy(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Enemy::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	texture.loadFromImage(gv->enemyImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	currentVelocity = sf::Vector2f(0.6f, 0.6f);
	maxSpeed = 5.f;
	HP = 100;
	maxHP = HP;
	shootDelay = 2.f;
	shootTime = 0.f;

	shootOffset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // random number generation from 0.0 to 1.0.
	moveTargetPos.x = static_cast<float>(0 + rand() % 5000);
	moveTargetPos.y = static_cast<float>(0 + rand() % 5000);

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);

	icon.setFillColor(sf::Color::Red);
	icon.setRadius(static_cast<float>(gv->enemyImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);

	shootClock.restart();
}

void Enemy::update(std::unique_ptr<GameVariable>& gv)
{
	if (isAlive)
	{
		updateHPBar();
		shootTime = (shootClock.getElapsedTime().asSeconds() + shootOffset) - menuTime;
		if (shootTime >= shootDelay)
		{
			isShoot = true;
			menuTime = 0;
			shootClock.restart();
			moveTargetPos.x = static_cast<float>(0 + rand() % 5000);
			moveTargetPos.y = static_cast<float>(0 + rand() % 5000);
		}
		rotate(gv, std::move(aimPos));
		move(gv);
		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);
		icon.setPosition(sprite.getPosition());
		rectHitbox.setPosition(sprite.getPosition());
		if (HP <= 0) { isAlive = false; } // if the enemy's health is zero or less, then isAlive is false.
	}
}

void Enemy::move(std::unique_ptr<GameVariable>& gv) { moveToTarget(gv, moveTargetPos); }

void Enemy::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
}