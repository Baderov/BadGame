#pragma once // защита от повторного включения.
#include <SFML/Graphics.hpp> // подключаем библиотеку.
#include "Variables.h" // подключаем заголовочный файл.
#include "Resolution.h"

void graphicsSettingsMenu(GameVariables* gv);

void settingsMenu(GameVariables* gv);

void mainMenu(GameVariables* gv); // функция запуска меню.

void menuEventHandler(GameVariables* gv);