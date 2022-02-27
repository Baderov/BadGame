#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Player.h" // подключаем заголовочный файл.

void setGameInfo(GameVariables* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities); // функция установки игровой информации.

void drawGameInfo(GameVariables* gv); // функция рисовки игровой информации.