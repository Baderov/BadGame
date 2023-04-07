#include "pch.h"
#include "Minimap.h" // header file for minimap.

Minimap::Minimap(sf::Vector2f gameViewSize, sf::Vector2f minimapCenter, sf::Vector2f minimapSize, sf::Vector2f viewportPos, sf::Vector2f viewportSize)
{
	setViewCenter(minimapCenter);
	setViewSize(minimapSize);
	setViewport(viewportPos, viewportSize);
	view.zoom(1.1f);


	border.setSize(sf::Vector2f(viewportSize.x * gameViewSize.x, viewportSize.y * gameViewSize.y));
	border.setPosition(0.f, 0.f);
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Black);
}

sf::View Minimap::getView()
{
	sf::View tempView = view;
	return tempView;
}

sf::FloatRect Minimap::getViewport()
{
	sf::FloatRect tempViewport = view.getViewport();
	return tempViewport;
}

void Minimap::setViewCenter(sf::Vector2f center)
{
	view.setCenter(center);
}
void Minimap::setViewSize(sf::Vector2f size)
{
	view.setSize(size);
}
void Minimap::setViewport(sf::Vector2f pos, sf::Vector2f size)
{
	view.setViewport(sf::FloatRect(pos, size));
}

void Minimap::setBorderSize(sf::Vector2f size)
{
	border.setSize(size);
}

void Minimap::setBorderPos(sf::Vector2f pos)
{
	border.setPosition(pos);
}

void Minimap::drawBorder(GameVariable* gv)
{
	if (gv->getShowMinimap() == true) { gv->window.draw(border); }
}