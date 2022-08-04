#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.

class Player : public Entity // create a player class and inherit it from Entity.
{
public:
	Player(sf::Image& image, sf::Vector2f startPos, std::wstring name); // player constructor.
	void update(GameVariables* gv); // player update function.
	void rotate(GameVariables* gv); // player rotate function.
	void move(GameVariables* gv); // player move function.
	void updateLaser(GameVariables* gv); // laser update function.
	void updateReloadRect(); // update reload rect function.
};