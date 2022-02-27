#include "Box.h" // подключаем заголовочный файл.

Box::Box(sf::Image& image, sf::Vector2f startPos, std::string name) : Entity(image, startPos, name)
{
	isAlive = true;
	HP = 30;
	rectHitbox.setFillColor(sf::Color::Blue);
}

void Box::update(GameVariables* gv) // функция update (в параметрах передаем время).
{
	if (isAlive == true) // если пуля жива, то:
	{
		if (HP <= 0) { isAlive = false; }	
		rectHitbox.setPosition(currentPos);
		sprite.setPosition(currentPos);
	}
}

void Box::move(GameVariables* gv)
{
	
}