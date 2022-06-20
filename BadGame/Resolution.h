#pragma once // защита от повторного включения.
#include <SFML/Graphics.hpp> // подключаем библиотеку.
#include "Variables.h" // подключаем заголовочный файл.
#include "Authorization.h"

void graphicsSettingsMenuUpdate(GameVariables* gv);

void settingsMenuUpdate(GameVariables* gv);

void mainMenuUpdate(GameVariables* gv, Entity*& player);

void authorizationUpdate(GameVariables* gv);

void multiplayerMenuUpdate(GameVariables* gv);