#pragma once // ������ �� ���������� ���������.
#include <SFML/Graphics.hpp> // ���������� ����������.
#include "Variables.h" // ���������� ������������ ����.
#include "Authorization.h"

void graphicsSettingsMenuUpdate(GameVariables* gv);

void settingsMenuUpdate(GameVariables* gv);

void mainMenuUpdate(GameVariables* gv, Entity*& player);

void authorizationUpdate(GameVariables* gv);

void multiplayerMenuUpdate(GameVariables* gv);