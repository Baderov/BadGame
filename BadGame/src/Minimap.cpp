#include "pch.h"
#include "Minimap.h" 

Minimap::Minimap()
{
	create();
}

void Minimap::create()
{
	sf::Vector2f gameViewSize = sf::Vector2f(1920.f, 1080.f);
	sf::Vector2f minimapCenter = sf::Vector2f(0.f, 0.f);
	sf::Vector2f minimapSize = sf::Vector2f(5000.f, 5000.f);
	sf::Vector2f viewportPos = sf::Vector2f(0.8f, 0.f);
	sf::Vector2f viewportSize = sf::Vector2f(0.2f, 0.355f);

	setViewCenter(std::move(minimapCenter));
	setViewSize(std::move(minimapSize));
	setViewport(std::move(viewportPos), std::move(viewportSize));
	view.zoom(1.1f);

	border.setSize(sf::Vector2f(getViewport().width * gameViewSize.x, getViewport().height * gameViewSize.y));
	border.setPosition(0.f, 0.f);
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Black);
}

void Minimap::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw)
{
	if (gv->getShowMinimap())
	{
		setViewCenter(sf::Vector2f((view.getSize().x / 2.f) - 300.f, (view.getSize().y / 2.f) - 250.f));
		setBorderPos(sf::Vector2f(gw->getGameViewCenter().x + (0.3f * gw->getGameViewSize().x), gw->getGameViewCenter().y - (0.5f * gw->getGameViewSize().y)));
	}
}

void Minimap::setView(std::unique_ptr<GameWindow>& gw)
{
	gw->window.setView(view);
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

void Minimap::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw)
{
	if (gv->getShowMinimap()) { gw->window.draw(border); }
}

