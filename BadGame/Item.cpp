#include "pch.h"
#include "ObjectPool.hpp"
#include "Item.h" 

Item::Item(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Item::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	if (this->name == L"GoldCoin") { texture.loadFromImage(gv->goldCoinImage); }
	else if (this->name == L"HPBonus") { texture.loadFromImage(gv->hpBonusImage); }

	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	rectHitbox.setSize(static_cast<sf::Vector2f>(texture.getSize()));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
	rectHitbox.setPosition(this->startPos);
}

void Item::update(std::unique_ptr<GameVariable>& gv) {}
void Item::move(std::unique_ptr<GameVariable>& gv) {}
void Item::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}