#include "pch.h"
#include "Bullet.h" // header file for bullets.

Bullet::Bullet(sf::Image& image, sf::Vector2f startPos, std::wstring name, std::wstring creatorName, sf::Vector2f aimPos) : Entity(image, startPos, name) // bullet constructor.
{
	entityType = "Bullet";
	this->creatorName = creatorName;
	isMove = true;
	currentVelocity = sf::Vector2f(0.3f, 0.3f);
	maxSpeed = 60.f;
	HP = 10;
	rectHitbox.setFillColor(sf::Color::Magenta);
	this->aimPos = aimPos;
	calcDirection();
}
void Bullet::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{
	if (isAlive == true) // if bullet is alive, then:
	{
		move(aimLaser, dt, isSinglePlayer);
		rectHitbox.setPosition(sprite.getPosition());
	}
}
void Bullet::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer)
{
	moveToDirection();
}
void Bullet::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{

}