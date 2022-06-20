#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Text.h" // ���������� ������������ ����.
#include "GameUpdate.h" // ���������� ������������ ����.
#include "Console.h" // ���������� ������������ ����.
#include "Authorization.h"
#include "Item.h"
#include "Menu.h"
#include "Network.h"

void updateTime(GameVariables* gv); // ������� ���������� �������.

void updateFPS(GameVariables* gv); // ������� ���������� FPS.

void eventHandler(sf::Event& event, GameVariables* gv); // ������� ��������� �������.

int main(); // ������� ������� ���������.