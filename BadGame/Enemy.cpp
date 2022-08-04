#include "Enemy.h" // header file for enemies.

Enemy::Enemy(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // enemy constructor.
{
	currentVelocity = sf::Vector2f(0.4f, 0.4f);
	maxSpeed = 5.f;
	HP = 100;
	maxHP = HP;
	shootDelay = 2000;
	shootTime = 0;
	shootOffset = 0 + rand() % (shootDelay / 2);
	moveTargetPos.x = static_cast<float>(0 + rand() % 3000);
	moveTargetPos.y = static_cast<float>(0 + rand() % 3000);

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(sf::Vector2f(h, h));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
}

void Enemy::update(GameVariables* gv) // enemy update function.
{
	if (isAlive == true)
	{
		updateHPBar();
		shootTime = (shootClock.getElapsedTime().asMilliseconds() + shootOffset) - menuTime;		
		if (shootTime >= shootDelay)
		{
			isShoot = true;
			menuTime = 0;
			shootClock.restart();
			moveTargetPos.x = static_cast < float>(0 + rand() % 3000);
			moveTargetPos.y = static_cast < float>(0 + rand() % 3000);
		}
		rotate();
		move(gv);
		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);
		sprite.setPosition(currentPos);
		rectHitbox.setPosition(currentPos);
		if (HP <= 0) { isAlive = false; } // if the enemy's health is zero or less, then isAlive is false.
	}
}

void Enemy::rotate() // enemy rotate function.
{
	float dX = aimPos.x - currentPos.x;
	float dY = aimPos.y - currentPos.y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees.
	sprite.setRotation(rotation);
}

void Enemy::move(GameVariables* gv) // enemy move function.
{
	moveToTarget(moveTargetPos, gv);	
}