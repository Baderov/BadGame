#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include "GameVariable.h"
#include "GameWindow.h"

enum class MenuType
{
	MainMenu, GameMenu, MultiplayerMenu, SettingsMenu, GraphicsSettingsMenu
}; inline MenuType menuType;

class MenuBackground
{
private:
	sf::VertexArray pointsArray;
	sf::Text BadGameText;
	sf::Clock colorClock;
	int ARRAY_SIZE;
	int colorTime;
public:
	MenuBackground();

	void init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);

	void movePoints(std::unique_ptr<GameWindow>& gw);
	void changeBadGameTextColor();

	void update(std::unique_ptr<GameWindow>& gw);
	void draw(std::unique_ptr<GameWindow>& gw);

};

#endif