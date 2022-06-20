#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Text.h" // подключаем заголовочный файл.
#include "GameUpdate.h" // подключаем заголовочный файл.
#include "Console.h" // подключаем заголовочный файл.
#include "Authorization.h"
#include "Item.h"
#include "Menu.h"
#include "Network.h"

void updateTime(GameVariables* gv); // функция обновления времени.

void updateFPS(GameVariables* gv); // функция обновления FPS.

void eventHandler(sf::Event& event, GameVariables* gv); // функция обработки событий.

int main(); // главная функция программы.