#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.

class Wall : public Entity // ������ ����� ������� � ��������� ��� �� Entity.
{
public:
	Wall(sf::Image& image, sf::Vector2f startPos, std::string name); // ����������� ������.
	void update(GameVariables* gv); // ������� ���������� ������ �������. (� ���������� �������� �����).
	void move(GameVariables* gv);
};