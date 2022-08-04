#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Wall : public Entity // create a wall class and inherit it from Entity.
{
public:
	Wall(sf::Image& image, sf::Vector2f startPos, std::wstring name); // wall constructor.
	void update(GameVariables* gv); // wall update function.
	void move(GameVariables* gv); // wall move function.
};