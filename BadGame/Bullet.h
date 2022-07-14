#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.

class Bullet : public Entity // ������ ����� ���� � ��������� ��� �� Entity.
{
public:
	Bullet(sf::Image& image, sf::Vector2f startPos, std::wstring name, std::wstring creatorName, sf::Vector2f aimPos); // ����������� ������.
	void update(GameVariables* gv); // ������� ���������� ������ �������. (� ���������� �������� �����).
	void move(GameVariables* gv);
};