#pragma once
#include "Variables.h"
#include "Entity.h"

class Item : public Entity
{
public:
	Item(sf::Image& image, sf::Vector2f startPos, std::wstring name);
	void update(GameVariables* gv);
	void move(GameVariables* gv);
};