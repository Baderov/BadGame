#pragma once // used to provide additional control at compile time.
#include <chrono> // time library.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.
#include "Bullet.h" // header file for bullets.
#include "Player.h" // header file for player.
#include "Box.h" // header file for boxes.
#include "Enemy.h" // header file for enemies.
#include "Wall.h" // header file for walls.
#include "Item.h" // header file for items.
#include "Network.h"
#include "Minimap.h" // header file for minimap.
#include "Text.h" // header file for working with text.

Entity* getPlayerPtr();

void setPlayerPtr(Entity* ptr);

bool s_enterMenu(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec, Minimap& minimap); // enter menu for singleplayer.

void collisionHandler(Entity* entity, Entity* entity2);

void applyButtonPressed(GameVariable* gv, Minimap& minimap);

void graphicsSettingsMenuUpdate(GameVariable* gv, Minimap& minimap); // graphic settings menu update function.

void settingsMenuUpdate(GameVariable* gv); // settings menu update function.

void mainMenuUpdate(GameVariable* gv); // main menu update function.

void multiplayerMenuUpdate(GameVariable* gv); // multiplayer menu update function.

void restartGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entities); // game restart function.

void updateGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entities); // entity update function.

void drawMinimap(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entities);

void drawEntities(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entities, Minimap& minimap);

void drawGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entities, Minimap& minimap); // entity drawing function.