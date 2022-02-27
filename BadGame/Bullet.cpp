#include "Bullet.h" // ���������� ������������ ����.

Bullet::Bullet(sf::Image& image, sf::Vector2f startPos, std::string name, std::string creatorName, sf::Vector2f aimPos) : Entity(image, startPos, name) // �� ��� ��, ������ ����� � ����� ��������� ������. (int dir)
{
	this->creatorName = creatorName;
	isMove = true;
	currentVelocity = sf::Vector2f(0.3f, 0.3f);
	maxSpeed = 40.f;
	HP = 10;
	rectHitbox.setFillColor(sf::Color::Magenta);
	this->aimPos = aimPos;
	calcDirection();
}

void Bullet::update(GameVariables* gv) // ������� update (� ���������� �������� �����).
{
	if (isAlive == true) // ���� ���� ����, ��:
	{
		move(gv);

		if ((currentPos.x <= 0) || (currentPos.y <= 0) || (currentPos.x >= 2936.f) || (currentPos.y >= 2936.f))
		{
			isAlive = false;
		}
		sprite.setPosition(currentPos);
		rectHitbox.setPosition(currentPos);
	}
}

void Bullet::move(GameVariables* gv)
{
	moveToDirection();
}