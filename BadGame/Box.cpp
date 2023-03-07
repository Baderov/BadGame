#include "Box.h" // header file for boxes.

Box::Box(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // box constructor.
{
	entityType = "Box";
	isAlive = true;
	HP = 30;
	rectHitbox.setFillColor(sf::Color::Blue);
}

void Box::update(GameVariable* gv) // box update function.
{
	if (isAlive == true) // if box is alive, then:
	{
		if (HP <= 0) { isAlive = false; }	
		rectHitbox.setPosition(currentPos);
		sprite.setPosition(currentPos);
	}
}

void Box::move(GameVariable* gv) // box move function.
{
	
}