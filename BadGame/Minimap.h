#ifndef MINIMAP_H
#define MINIMAP_H

#include "Variables.h"

class Minimap
{
private:
	sf::View view;
	sf::RectangleShape border;
public:
	Minimap(sf::Vector2f gameViewSize, sf::Vector2f minimapCenter, sf::Vector2f minimapSize, sf::Vector2f viewportPos, sf::Vector2f viewportSize);

	void update(std::unique_ptr<GameVariable>& gv);

	void setView(std::unique_ptr<GameVariable>& gv);
	void setViewCenter(sf::Vector2f center);
	void setViewSize(sf::Vector2f size);
	void setViewport(sf::Vector2f pos, sf::Vector2f size);
	void setBorderSize(sf::Vector2f size);
	void setBorderPos(sf::Vector2f pos);

	sf::FloatRect getViewport();
	sf::Vector2f getViewSize();

	void draw(std::unique_ptr<GameVariable>& gv);
};

#endif