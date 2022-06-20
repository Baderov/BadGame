#pragma once // защита от повторного включения.
#include <chrono> // подключаем библиотеку.
#include "Variables.h" // подключаем заголовочный файл.
#include "Entity.h" // подключаем заголовочный файл.
#include "Bullet.h" // подключаем заголовочный файл.
#include "Player.h" // подключаем заголовочный файл.
#include "Box.h" // подключаем заголовочный файл.
#include "Collision.h" // подключаем заголовочный файл.
#include "Enemy.h" // подключаем заголовочный файл.
#include "Wall.h" // подключаем заголовочный файл.
#include "Item.h" // подключаем заголовочный файл.

void boxSpawn(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities);

void restartGame(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, Entity*& player);

void updateEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2, Entity*& player); // функция обновления сущностей.

void drawEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it); // функция рисовки сущностей.