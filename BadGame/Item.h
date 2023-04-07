#pragma once // used to provide additional control at compile time.
#include "Entity.h" // header file for entities.

class Item : public Entity // create an Item class and inherit it from Entity.
{
public:
	Item(sf::Image& image, sf::Vector2f startPos, std::wstring name); // item constructor.
	void update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer) override;
	void move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) override;
	void rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos) override;
};