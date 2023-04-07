#pragma once // used to provide additional control at compile time.
#include "Entity.h" // header file for entities.

class Box : public Entity // create a box class and inherit it from Entity.
{
public:
	Box(sf::Image& image, sf::Vector2f startPos,  std::wstring name); // box constructor.
	void update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer) override;
	void move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) override;
	void rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos) override;
};