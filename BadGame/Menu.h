#pragma once // ������ �� ���������� ���������.
#include <SFML/Graphics.hpp> // ���������� ����������.
#include "Variables.h" // ���������� ������������ ����.
#include "Resolution.h"

void graphicsSettingsMenu(GameVariables* gv);

void settingsMenu(GameVariables* gv);

void mainMenu(GameVariables* gv); // ������� ������� ����.

void menuEventHandler(GameVariables* gv);