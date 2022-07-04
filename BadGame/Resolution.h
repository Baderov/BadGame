#pragma once // ������ �� ���������� ���������.
#include <SFML/Graphics.hpp> // ���������� ����������.
#include "Variables.h" // ���������� ������������ ����.
#include "GameUpdate.h" 
#include "Keyboard.h"

void graphicsSettingsMenuUpdate(GameVariables* gv);

void settingsMenuUpdate(GameVariables* gv);

void mainMenuUpdate(GameVariables* gv, Entity*& player);

void multiplayerMenuUpdate(GameVariables* gv);