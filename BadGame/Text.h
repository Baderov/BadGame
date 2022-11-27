#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Player.h" // header file for player.

void setGameInfo(GameVariable* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities); // function for setting game information.

void drawGameInfo(GameVariable* gv); // function for drawing game information.