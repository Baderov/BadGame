#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.

class Enemy : public Entity // ������ ����� ������ � ��������� ��� �� Entity.
{
public:
	Enemy(sf::Image& image, sf::Vector2f startPos, std::string name); // ����������� ������.
	void update(GameVariables* gv);
	void move(GameVariables* gv);
	void rotate();
private:
	sf::Clock shootClock;
	int shootTime;
	int shootDelay;
	int shootOffset;
};