#ifndef MINIMAP_H
#define MINIMAP_H

#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"

class Minimap
{
private:
	sf::View view;
	sf::RectangleShape border;
public:
	Minimap();

	void create();

	void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);

	void setView(std::unique_ptr<GameWindow>& gw);
	void setViewCenter(sf::Vector2f center);
	void setViewSize(sf::Vector2f size);
	void setViewport(sf::Vector2f pos, sf::Vector2f size);
	void setBorderSize(sf::Vector2f size);
	void setBorderPos(sf::Vector2f pos);

	sf::FloatRect getViewport();
	sf::Vector2f getViewSize();

	void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);
};

#endif