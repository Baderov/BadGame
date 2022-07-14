#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Text.h" // ���������� ������������ ����.
#include "GameUpdate.h" // ���������� ������������ ����.
#include "Console.h" // ���������� ������������ ����.
#include "Item.h"
#include "Menu.h"

void updateFPS(GameVariables* gv); // ������� ���������� FPS.

void updateTime(GameVariables* gv);

void eventHandler(sf::Event& event, GameVariables* gv, Chat& chat); // ������� ��������� �������.

void singleplayerGame(GameVariables* gv, Chat& chat);

void logs(GameVariables* gv);

int main(); // ������� ������� ���������.