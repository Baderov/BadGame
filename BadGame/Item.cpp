#include "pch.h"
#include "Item.h" // header file for items.

Item::Item(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // item constructor.
{
	entityType = "Item";
}

void Item::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{

}
void Item::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer)
{

}
void Item::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{

}