#include "Wall.h" // header file for walls.

Wall::Wall(sf::Vector2f startPos, std::wstring name, sf::Vector2f size) : Entity(startPos, name) // wall constructor.
{
	rectHitbox.setSize(size);
	rectHitbox.setOrigin(0.f, 0.f);
	if (name == L"LeftWall" || name == L"RightWall") { rectHitbox.setRotation(90); }
	rectHitbox.setFillColor(sf::Color(153, 0, 76));
}

void Wall::update(GameVariable* gv) // wall update function.
{
	rectHitbox.setPosition(currentPos);
}

void Wall::move(GameVariable* gv) // wall move function.
{
}