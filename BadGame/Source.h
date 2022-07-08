#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Text.h" // ���������� ������������ ����.
#include "GameUpdate.h" // ���������� ������������ ����.
#include "Console.h" // ���������� ������������ ����.
#include "Item.h"
#include "Menu.h"

void updateTime(GameVariables* gv); // ������� ���������� �������.

void updateFPS(GameVariables* gv); // ������� ���������� FPS.

void eventHandler(sf::Event& event, GameVariables* gv); // ������� ��������� �������.

void singleplayerGame(GameVariables* gv);

int main(); // ������� ������� ���������.