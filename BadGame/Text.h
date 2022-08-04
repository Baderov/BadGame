#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Player.h" // header file for player.

void setGameInfo(GameVariables* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities); // function for setting game information.

void drawGameInfo(GameVariables* gv); // function for drawing game information.