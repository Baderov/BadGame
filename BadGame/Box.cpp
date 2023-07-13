#include "pch.h"
#include "ObjectPool.hpp"
#include "Box.h" 

Box::Box(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Box::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

	HP = 30;

	texture.loadFromImage(gv->boxImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	rectHitbox.setSize(sf::Vector2f(texture.getSize()));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
	rectHitbox.setPosition(this->startPos);

	icon.setRadius(static_cast<float>(gv->boxImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);

	rectHitbox.setFillColor(sf::Color::Blue);
}

void Box::update(std::unique_ptr<GameVariable>& gv)
{
	if (isAlive) // if box is alive, then:
	{
		if (HP <= 0) { isAlive = false; }
		rectHitbox.setPosition(sprite.getPosition());
	}
}
void Box::move(std::unique_ptr<GameVariable>& gv) {}
void Box::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) {}