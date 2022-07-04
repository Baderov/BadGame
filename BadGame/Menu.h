#pragma once // защита от повторного включения.
#include <SFML/Graphics.hpp> // подключаем библиотеку.
#include "Variables.h" // подключаем заголовочный файл.
#include "Resolution.h"
#include "Network.h"
#include "GameUpdate.h" 
#include "Keyboard.h"

void graphicsSettingsMenu(GameVariables* gv);

void settingsMenu(GameVariables* gv);

void mainMenu(GameVariables* gv, Entity*& player); // функция запуска меню.

void menuEventHandler(GameVariables* gv, Entity*& player);

void errorChecking(GameVariables* gv);