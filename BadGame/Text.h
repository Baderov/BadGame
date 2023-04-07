#pragma once // used to provide additional control at compile time.
#include "Player.h" // header file for player.
#include "Enemy.h"

void setGameInfo(GameVariable* gv, Entity* player, size_t entitiesVecSize); // function for setting game information.

void drawGameInfo(GameVariable* gv); // function for drawing game information.