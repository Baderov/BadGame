#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Enemy::enemyID = 0;

void Enemy::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos)
{
	enemyID++;

	isAlive = true;
	isMove = true;
	isCollision = false;

	this->startPos = std::move(startPos);

	name = L"Enemy" + std::to_wstring(enemyID);

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

	collisionRect.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	collisionRect.setOrigin(collisionRect.getSize().x / 2.f, collisionRect.getSize().y / 2.f);
	collisionRect.setPosition(this->startPos);
	collisionRect.setFillColor(sf::Color::Red);

	icon.setFillColor(sf::Color::Red);
	icon.setRadius(static_cast<float>(gv->enemyImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);

	shootClock.restart();
}

void Enemy::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isAlive)
	{
		move(gv, gw, sm, nm);
		shoot(gv, sm);
		rotate(gv, aimPos);
		updateHPBar();

		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);
		icon.setPosition(sprite.getPosition());
		if (HP <= 0) { isAlive = false; } // if the enemy's health is zero or less, then isAlive is false.
	}
	else
	{
		dropItem(gv);
		returnToPool(gv, gw, sm, nm);
	}
}

void Enemy::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isMove)
	{
		calcTarget(moveTargetPos, gv->getDT());
		moveCollisionRect();
		collision(gv, gw, sm, nm);
		if (isCollision) { returnCollisionRect(); }
		else { sprite.move(stepPos); }
	}
}

void Enemy::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (nm->getIsMinimapView()) { drawIcon(gw); }
	else
	{
		if (gv->getShowCollisionRect()) { drawCollisionRect(gw); }
		else
		{
			drawSprite(gw);
			drawHPBarOuter(gw);
			drawHPBarInner(gw);
			drawHPText(gw);
		}
	}
}

void Enemy::collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
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
}

void Enemy::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < enemiesVec.size(); ++i)
	{
		if (enemiesVec[i]->getName() == name)
		{
			enemiesPool.returnToPool(enemiesVec, enemiesVec[i]);
			break;
		}
	}
}

void Enemy::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
}

void Enemy::dropItem(std::unique_ptr<GameVariable>& gv)
{
	int numOfItems = 0 + rand() % 6;

	for (int i = 0; i < numOfItems; ++i)
	{
		if (itemsPool.getFromPool(itemsVec))
		{
			itemsVec.back()->init(gv, sf::Vector2f(sprite.getPosition().x + (i * 15), sprite.getPosition().y), ItemType::GoldCoin);
		}
	}
}

void Enemy::shoot(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm)
{
	aimPos = playerPtr->getSpritePos();

	if (isShoot)
	{
		float distance = sqrt(((aimPos.x - sprite.getPosition().x) * (aimPos.x - sprite.getPosition().x)) + ((aimPos.y - sprite.getPosition().y) * (aimPos.y - sprite.getPosition().y)));

		if (distance < 750.f && bulletsPool.getFromPool(bulletsVec))
		{
			bulletsVec.back()->init(gv, sprite.getPosition(), aimPos, name);
		}

		isShoot = false;
	}

	shootTime = (shootClock.getElapsedTime().asSeconds() + shootOffset) - sm->getMenuTime();
	if (shootTime >= shootDelay)
	{
		isShoot = true;
		isMove = true;
		isCollision = false;
		moveTargetPos.x = static_cast<float>(0 + rand() % 5000);
		moveTargetPos.y = static_cast<float>(0 + rand() % 5000);
		sm->setMenuTime(0.f);
		shootClock.restart();
	}
}