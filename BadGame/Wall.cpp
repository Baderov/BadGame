#include "pch.h"
#include "Wall.h" // header file for walls.

Wall::Wall(sf::Vector2f startPos, std::wstring name, sf::Vector2f size) : Entity(startPos, name) // wall constructor.
{
	entityType = "Wall";
	rectHitbox.setSize(size);
	rectHitbox.setOrigin(0.f, 0.f);
	if (name == L"LeftWall" || name == L"RightWall") { rectHitbox.setRotation(90); }
	rectHitbox.setFillColor(sf::Color(153, 0, 76));
	rectHitbox.setPosition(startPos);
}
void Wall::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{

}
void Wall::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer)
{

}
void Wall::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{

}