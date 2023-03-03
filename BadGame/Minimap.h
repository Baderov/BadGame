#pragma once
#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include "Variables.h"
class Minimap
{
private:
	sf::View view;
	sf::RectangleShape border;
public:
	Minimap(sf::Vector2f gameViewSize, sf::Vector2f minimapCenter, sf::Vector2f minimapSize, sf::Vector2f viewportPos, sf::Vector2f viewportSize);
	sf::View getView();
	sf::FloatRect getViewport();
	void setViewCenter(sf::Vector2f center);
	void setViewSize(sf::Vector2f size);
	void setViewport(sf::Vector2f pos, sf::Vector2f size);
	void setBorderSize(sf::Vector2f size);
	void setBorderPos(sf::Vector2f pos);
	void drawBorder(GameVariable* gv);
};

