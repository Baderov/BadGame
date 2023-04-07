#include "pch.h"
#include "Enemy.h" // header file for enemies.

Enemy::Enemy(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // enemy constructor.
{
	entityType = "Enemy";

	numOfEnemies++;

	currentVelocity = sf::Vector2f(0.4f, 0.4f);
	maxSpeed = 5.f;
	HP = 100;
	maxHP = HP;
	shootDelay = 2.f;
	shootTime = 0.f;
	shootOffset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // random number generation from 0.0 to 1.0.
	moveTargetPos.x = static_cast<float>(0 + rand() % 5000);
	moveTargetPos.y = static_cast<float>(0 + rand() % 5000);

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(sf::Vector2f(h, h));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);

	icon.setFillColor(sf::Color::Red);
}

void Enemy::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{
	if (isAlive == true)
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
		rotate(aimLaser, aimPos);
		move(aimLaser, dt, isSinglePlayer);
		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);
		icon.setPosition(sprite.getPosition());
		rectHitbox.setPosition(sprite.getPosition());
		if (HP <= 0) { isAlive = false; } // if the enemy's health is zero or less, then isAlive is false.
	}
}
void Enemy::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer)
{
	moveToTarget(moveTargetPos, dt, isSinglePlayer);
}
void Enemy::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{
	float dX = targetPos.x - sprite.getPosition().x;
	float dY = targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
}