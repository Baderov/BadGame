#include "pch.h"
#include "Box.h"

Box::Box(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Box::boxID = 0;

void Box::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos)
{
	boxID++;

	isAlive = true;

	this->startPos = std::move(startPos);
	name = L"Box" + std::to_wstring(boxID);

	HP = 30;

	texture.loadFromImage(gv->boxImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	collisionRect.setSize(sf::Vector2f(texture.getSize()));
	collisionRect.setOrigin(collisionRect.getSize().x / 2.f, collisionRect.getSize().y / 2.f);
	collisionRect.setPosition(this->startPos);
	collisionRect.setFillColor(sf::Color::Blue);

	icon.setRadius(static_cast<float>(gv->boxImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);
}

void Box::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isAlive)
	{
		if (HP <= 0) { isAlive = false; }
	}
	else
	{
		dropItem(gv);
		returnToPool(gv, gw, sm, nm);
	}
}
void Box::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Box::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getShowCollisionRect()) { drawCollisionRect(gw); }
	else { drawSprite(gw); }
}

void Box::collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Box::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < boxesVec.size(); ++i)
	{
		if (boxesVec[i]->getName() == name)
		{
			boxesPool.returnToPool(boxesVec, boxesVec[i]);
			break;
		}
	}
}

void Box::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}

void Box::dropItem(std::unique_ptr<GameVariable>& gv)
{
	int itemType = 0 + rand() % 3;
	int numOfItems = 0;

	if (itemType == 1)
	{
		numOfItems = 0 + rand() % 2;
		for (int i = 0; i < numOfItems; ++i)
		{
			if (itemsPool.getFromPool(itemsVec))
			{
				itemsVec.back()->init(gv, sf::Vector2f(sprite.getPosition().x + (i * 15), sprite.getPosition().y), ItemType::Health);
			}
		}
	}
	else if (itemType == 2)
	{
		numOfItems = 0 + rand() % 6;
		for (int i = 0; i < numOfItems; ++i)
		{
			if (itemsPool.getFromPool(itemsVec))
			{
				itemsVec.back()->init(gv, sf::Vector2f(sprite.getPosition().x + (i * 15), sprite.getPosition().y), ItemType::GoldCoin);
			}
		}
	}
}