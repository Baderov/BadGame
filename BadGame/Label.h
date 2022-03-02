#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Label
{
public:
	Label(std::wstring str, sf::Vector2f labelPos, int textSize, std::string name);
	sf::Text& getText();
	std::string& getName();
private:
	sf::Text text;
	sf::Font font;
	std::string name;
};
