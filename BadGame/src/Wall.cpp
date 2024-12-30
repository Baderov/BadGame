#include "pch.h"
#include "Wall.h"

Wall::Wall(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

unsigned int Wall::wallID = 0;

void Wall::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, WallType wallType)
{
	wallID++;

	isAlive = true;

	this->wallType = std::move(wallType);
	this->startPos = std::move(startPos);

	name = L"Wall" + std::to_wstring(wallID);

	texture.loadFromImage(gv->wallImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(0.f, 0.f);
	sprite.setPosition(this->startPos);

	collider.setSize(sf::Vector2f(texture.getSize()));
	collider.setOrigin(0.f, 0.f);
	collider.setPosition(this->startPos);
	collider.setFillColor(sf::Color::Blue);

	if (wallType == WallType::LeftWall || wallType == WallType::RightWall) { sprite.setRotation(90); collider.setRotation(90); }
}

void Wall::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Wall::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Wall::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (gv->getShowCollisionRect()) { drawCollider(gw); }
	else { drawSprite(gw); }
}

void Wall::checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Wall::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Wall::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}