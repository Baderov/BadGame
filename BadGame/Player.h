#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.
#include "Entity.h" // ���������� ������������ ����.

class Player : public Entity // ������ ����� ������ � ��������� ��� �� Entity.
{
public:
	Player(sf::Image& image, sf::Vector2f startPos, std::string name); // ����������� ������.
	void update(GameVariables* gv);
	void move(GameVariables* gv);
	void rotate(GameVariables* gv);
	void updateLaser(GameVariables* gv);
	void updateReloadRect();
};