#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f buttonSize, sf::Vector2f buttonPos, std::wstring str, int textSize, std::string name);
	sf::RectangleShape& getSprite();
	sf::Text& getText();
	std::string& getName();
private:
	sf::Text text;
	sf::RectangleShape sprite;
	sf::Font font;
	std::string name;
};
