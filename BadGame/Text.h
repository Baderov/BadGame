#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Player.h" // header file for player.

void setGameInfo(GameVariable* gv, Entity* player, size_t entitiesVecSize); // function for setting game information.

void drawGameInfo(GameVariable* gv); // function for drawing game information.