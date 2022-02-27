#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Player.h" // ���������� ������������ ����.

void setGameInfo(GameVariables* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities); // ������� ��������� ������� ����������.

void drawGameInfo(GameVariables* gv); // ������� ������� ������� ����������.