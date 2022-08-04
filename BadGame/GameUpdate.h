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

void graphicsSettingsMenuUpdate(GameVariables* gv); // graphic settings menu update function.

void settingsMenuUpdate(GameVariables* gv); // settings menu update function.

void mainMenuUpdate(GameVariables* gv, Entity*& player); // main menu update function.

void multiplayerMenuUpdate(GameVariables* gv); // multiplayer menu update function.

void boxSpawn(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities); // box spawn function.

void restartGame(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, Entity*& player); // game restart function.

void updateEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2, Entity*& player); // entity update function.

void drawEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it); // entity drawing function.