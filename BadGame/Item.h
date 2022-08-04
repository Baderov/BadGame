#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Item : public Entity // create an Item class and inherit it from Entity.
{
public:
	Item(sf::Image& image, sf::Vector2f startPos, std::wstring name); // item constructor.
	void update(GameVariables* gv); // item update function.
	void move(GameVariables* gv); // item move function.
};