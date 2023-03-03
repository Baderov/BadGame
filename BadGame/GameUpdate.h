#pragma once // used to provide additional control at compile time.
#include <chrono> // time library.
#include "Variables.h" // header file for global variables.
#include "Entity.h" // header file for entities.
#include "Bullet.h" // header file for bullets.
#include "Player.h" // header file for player.
#include "Box.h" // header file for boxes.
#include "Collision.h" // header file for collision handling.
#include "Enemy.h" // header file for enemies.
#include "Wall.h" // header file for walls.
#include "Item.h" // header file for items.
#include "Network.h"
#include "Minimap.h"

Entity* getPlayerPtr();

void applyButtonPressed(GameVariable* gv, Minimap& minimap);

void graphicsSettingsMenuUpdate(GameVariable* gv, Minimap& minimap); // graphic settings menu update function.

void settingsMenuUpdate(GameVariable* gv); // settings menu update function.

void mainMenuUpdate(GameVariable* gv); // main menu update function.

void multiplayerMenuUpdate(GameVariable* gv); // multiplayer menu update function.

void restartGame(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities); // game restart function.

void updateGame(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2); // entity update function.

void drawMinimap(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, Minimap& minimap);

void drawEntities(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, Minimap& minimap);

void drawGame(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, Minimap& minimap); // entity drawing function.