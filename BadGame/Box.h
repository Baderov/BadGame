#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Box : public Entity // create a box class and inherit it from Entity.
{
public:
	Box(sf::Image& image, sf::Vector2f startPos,  std::wstring name); // box constructor.
	void update(GameVariable* gv); // box update function.
	void move(GameVariable* gv); // box move function.
};