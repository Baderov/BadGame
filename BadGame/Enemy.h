#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Enemy : public Entity // create a enemy class and inherit it from Entity.
{
public:
	Enemy(sf::Image& image, sf::Vector2f startPos, std::wstring name); // enemy constructor.
	void update(GameVariables* gv); // enemy update function.
	void rotate(); // enemy rotate function.
	void move(GameVariables* gv); // enemy move function.
};