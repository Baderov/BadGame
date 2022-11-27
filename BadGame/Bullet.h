#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Bullet : public Entity // create a bullet class and inherit it from Entity.
{
public:
	Bullet(sf::Image& image, sf::Vector2f startPos, std::wstring name, std::wstring creatorName, sf::Vector2f aimPos); // bullet constructor.
	void update(GameVariable* gv); // bullet update function.
	void move(GameVariable* gv); // bullet move function.
};