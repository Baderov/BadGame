#ifndef TEXT_H
#define TEXT_H

#include "Player.h" // header file for player.
#include "Enemy.h"
#include "Box.h"
#include "Wall.h"
#include "Bullet.h"
#include "Item.h"
#include "ObjectPool.hpp"

void setTextsAndSprites(std::unique_ptr<GameVariable>& gv); // function for setting values for texts and sprites.

void setGameInfo(std::unique_ptr<GameVariable>& gv, Entity* player, float& fps); // function for setting game information.

void drawGameInfo(sf::RenderWindow& window, bool showLogs); // function for drawing game information.

#endif