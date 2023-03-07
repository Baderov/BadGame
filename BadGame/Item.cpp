#include "Item.h" // header file for items.

Item::Item(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // item constructor.
{
	entityType = "Item";
}

void Item::update(GameVariable* gv) // item update function.
{

}

void Item::move(GameVariable* gv) // item move function.
{

}