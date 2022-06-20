#pragma once // ������ �� ���������� ���������.
#include <chrono> // ���������� ����������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.
#include "Bullet.h" // ���������� ������������ ����.
#include "Player.h" // ���������� ������������ ����.
#include "Box.h" // ���������� ������������ ����.
#include "Collision.h" // ���������� ������������ ����.
#include "Enemy.h" // ���������� ������������ ����.
#include "Wall.h" // ���������� ������������ ����.
#include "Item.h" // ���������� ������������ ����.

void boxSpawn(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities);

void restartGame(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, Entity*& player);

void updateEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2, Entity*& player); // ������� ���������� ���������.

void drawEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it); // ������� ������� ���������.