#include "Wall.h" // подключаем заголовочный файл.

Wall::Wall(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name)
{
	sprite.setOrigin(0.f, 0.f);
	rectHitbox.setOrigin(0.f, 0.f);

	if (name == L"LeftWall" || name == L"RightWall")
	{
		sprite.setRotation(90);
		rectHitbox.setRotation(90);
	}
	rectHitbox.setFillColor(sf::Color::Magenta);
}

void Wall::update(GameVariables* gv) // функция update (в параметрах передаем время).
{
	rectHitbox.setPosition(currentPos);
	sprite.setPosition(currentPos);
}

void Wall::move(GameVariables* gv)
{
	
}