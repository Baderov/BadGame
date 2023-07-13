#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include "Collision.h"
#include "ObjectPool.hpp"
#include "Network.h"
#include "Minimap.h"
#include "Chat.h"
#include "PlayersList.h"
#include "Text.h"
#include "Variables.h"

bool s_enterMenu(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // enter menu for singleplayer.

void s_eventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // event handling function for singleplayer.

void respawnEnemies(std::unique_ptr<GameVariable>& gv);

void respawnBoxes(std::unique_ptr<GameVariable>& gv);

void respawnHPBonuses(std::unique_ptr<GameVariable>& gv);

void restartGame(std::unique_ptr<GameVariable>& gv); // game restart function.

void setGameResult(std::unique_ptr<GameVariable>& gv);

void updatePlayer(std::unique_ptr<GameVariable>& gv, float& fps);

void updateGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat, float& fps); // game update function. 



void drawGameResult(std::unique_ptr<GameVariable>& gv);

void drawPlayer(std::unique_ptr<GameVariable>& gv);

void drawMinimap(std::unique_ptr<GameVariable>& gv, Minimap& minimap);

void drawEntities(std::unique_ptr<GameVariable>& gv, Minimap& minimap);

void drawGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap);

#endif