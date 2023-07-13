#include "pch.h"
#include "Minimap.h" 

Minimap::Minimap(sf::Vector2f gameViewSize, sf::Vector2f minimapCenter, sf::Vector2f minimapSize, sf::Vector2f viewportPos, sf::Vector2f viewportSize)
{
	setViewCenter(std::move(minimapCenter));
	setViewSize(std::move(minimapSize));
	setViewport(std::move(viewportPos), std::move(viewportSize));
	view.zoom(1.1f);

	border.setSize(sf::Vector2f(getViewport().width * gameViewSize.x, getViewport().height * gameViewSize.y));
	border.setPosition(0.f, 0.f);
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Black);
}

void Minimap::update(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getShowMinimap())
	{
		setViewCenter(sf::Vector2f((view.getSize().x / 2.f) - 300.f, (view.getSize().y / 2.f) - 250.f));
		setBorderPos(sf::Vector2f(gv->getGameViewCenter().x + (0.3f * gv->getGameViewSize().x), gv->getGameViewCenter().y - (0.5f * gv->getGameViewSize().y)));
	}
}

void Minimap::setView(std::unique_ptr<GameVariable>& gv)
{
	gv->window.setView(view);
}

void Minimap::setViewCenter(sf::Vector2f center)
{
	view.setCenter(std::move(center));
}

void Minimap::setViewSize(sf::Vector2f size)
{
	view.setSize(std::move(size));
}

void Minimap::setViewport(sf::Vector2f pos, sf::Vector2f size)
{
	view.setViewport(sf::FloatRect(std::move(pos), std::move(size)));
}

void Minimap::setBorderSize(sf::Vector2f size)
{
	border.setSize(std::move(size));
}

void Minimap::setBorderPos(sf::Vector2f pos)
{
	border.setPosition(std::move(pos));
}

sf::FloatRect Minimap::getViewport()
{
	sf::FloatRect tempViewport = view.getViewport();
	return tempViewport;
}

sf::Vector2f Minimap::getViewSize()
{
	sf::Vector2f tempSize = view.getSize();
	return tempSize;
}

void Minimap::draw(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getShowMinimap()) { gv->window.draw(border); }
}

