#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Text.h" // подключаем заголовочный файл.
#include "GameUpdate.h" // подключаем заголовочный файл.
#include "Console.h" // подключаем заголовочный файл.
#include "Item.h"
#include "Menu.h"

void updateFPS(GameVariables* gv); // функция обновления FPS.

void updateTime(GameVariables* gv);

void eventHandler(sf::Event& event, GameVariables* gv, Chat& chat); // функция обработки событий.

void singleplayerGame(GameVariables* gv, Chat& chat);

void logs(GameVariables* gv);

int main(); // главная функция программы.