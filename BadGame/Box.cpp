#include "pch.h"
#include "Box.h" // header file for boxes.

Box::Box(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // box constructor.
{
	entityType = "Box";
	isAlive = true;
	HP = 30;
	rectHitbox.setFillColor(sf::Color::Blue);
}
void Box::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{
	if (isAlive == true) // if box is alive, then:
	{
		if (HP <= 0) { isAlive = false; }
		rectHitbox.setPosition(sprite.getPosition());
	}
}
void Box::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer)
{

}
void Box::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{

}