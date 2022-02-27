#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.

class Box : public Entity // ������ ����� ������� � ��������� ��� �� Entity.
{
public:
	Box(sf::Image& image, sf::Vector2f startPos,  std::string name); // ����������� ������.
	void update(GameVariables* gv); // ������� ���������� ������ �������. (� ���������� �������� �����).
	void move(GameVariables* gv);
};