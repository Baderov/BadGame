#include "pch.h"
#include "Item.h"

Item::Item(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Item::itemID = 0;

void Item::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, ItemType itemType)
{
	itemID++;

	isAlive = true;

	this->itemType = std::move(itemType);
	this->startPos = std::move(startPos);

	name = L"Item" + std::to_wstring(itemID);

	if (this->itemType == ItemType::GoldCoin) { texture.loadFromImage(gv->goldCoinImage); }
	else if (this->itemType == ItemType::Health) { texture.loadFromImage(gv->hpBonusImage); }

	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	collider.setSize(static_cast<sf::Vector2f>(texture.getSize()));
	collider.setOrigin(collider.getSize().x / 2.f, collider.getSize().y / 2.f);
	collider.setPosition(this->startPos);
	collider.setFillColor(sf::Color::Yellow);
}

void Item::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (!isAlive) { returnToPool(gv, gw, sm, nm); }
}

void Item::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Item::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getShowCollisionRect()) { drawCollider(gw); }
	else { drawSprite(gw); }
}

void Item::checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Item::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < itemsVec.size(); ++i)
	{
		if (itemsVec[i]->getName() == name)
		{
			itemsPool.returnToPool(itemsVec, itemsVec[i]);
			break;
		}
	}
}

void Item::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}