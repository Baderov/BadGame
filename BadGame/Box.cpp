#include "Box.h" // ���������� ������������ ����.

Box::Box(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name)
{
	isAlive = true;
	HP = 30;
	rectHitbox.setFillColor(sf::Color::Blue);
}

void Box::update(GameVariables* gv)
{
	if (isAlive == true) // ���� ���� ����, ��:
	{
		if (HP <= 0) { isAlive = false; }	
		rectHitbox.setPosition(currentPos);
		sprite.setPosition(currentPos);
	}
}

void Box::move(GameVariables* gv)
{
	
}