#include "pch.h"
#include "MenuBackground.h"

MenuBackground::MenuBackground() { ARRAY_SIZE = 0; colorTime = 0; }

void MenuBackground::init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw)
{
	BadGameText.setFont(gv->consolasFont);
	BadGameText.setOutlineThickness(3.f);
	BadGameText.setCharacterSize(70);
	BadGameText.setString("BADEROV'S GAME");
	BadGameText.setOrigin(BadGameText.getGlobalBounds().width / 2.f, BadGameText.getGlobalBounds().height / 2.f);
	BadGameText.setPosition(static_cast<float>(gw->getSize().x / 2.f), 100.f);

	ARRAY_SIZE = (gw->getSize().x * gw->getSize().y) / 41;

	pointsArray.setPrimitiveType(sf::Points);
	pointsArray.resize(ARRAY_SIZE);
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		pointsArray[i].position = sf::Vector2f(static_cast<float>(rand() % gw->getSize().x) + 0.5f, static_cast<float>(rand() % gw->getSize().y) + 0.5f);
		pointsArray[i].color = sf::Color::Red;
	}
}

void MenuBackground::movePoints(std::unique_ptr<GameWindow>& gw)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		pointsArray[i].position.y += 2;
		if (pointsArray[i].position.y >= gw->getSize().y)
		{
			pointsArray[i].position.x = static_cast<float>(rand() % gw->getSize().x) + 0.5f;
			pointsArray[i].position.y = 0 + 0.5f;
		}
	}
}

void MenuBackground::changeBadGameTextColor()
{
	colorTime = static_cast<int>(colorClock.getElapsedTime().asMilliseconds() * 0.1);

	BadGameText.setFillColor(sf::Color(127, 0, 255, colorTime));

	if (colorTime >= 255)
	{
		BadGameText.setFillColor(sf::Color(127, 0, 255, 50));
		colorClock.restart();
	}
}

void MenuBackground::update(std::unique_ptr<GameWindow>& gw)
{
	movePoints(gw);
	changeBadGameTextColor();
}

void MenuBackground::draw(std::unique_ptr<GameWindow>& gw) { gw->window.draw(pointsArray); if (menuType == MenuType::MainMenu) { gw->window.draw(BadGameText); } }