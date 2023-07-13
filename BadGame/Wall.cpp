#include "pch.h"
#include "ObjectPool.hpp"
#include "Wall.h" 

Wall::Wall(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Wall::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	texture.loadFromImage(gv->wallImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(0.f, 0.f);
	if (this->name == L"LeftWall" || this->name == L"RightWall") { sprite.setRotation(90); }
	sprite.setPosition(this->startPos);

	rectHitbox.setSize(sf::Vector2f(texture.getSize()));
	rectHitbox.setOrigin(0.f, 0.f);
	if (this->name == L"LeftWall" || this->name == L"RightWall") { rectHitbox.setRotation(90); }
	rectHitbox.setFillColor(sf::Color::Black);
	rectHitbox.setPosition(this->startPos);
}

void Wall::update(std::unique_ptr<GameVariable>& gv) {}
void Wall::move(std::unique_ptr<GameVariable>& gv) {}
void Wall::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}