#pragma once
#include <SFML/Graphics.hpp>
#include "RichText.hpp"
#include "Variables.h"
#include <windows.h>

struct chatStrings
{
	chatStrings(std::wstring prefix, std::wstring msg, int countOfLines)
	{
		this->prefix = prefix;
		this->msg = msg;
		this->countOfLines = countOfLines;
	}
	std::wstring prefix = L"";
	std::wstring msg = L"";
	int countOfLines = 1;
};

class Chat
{
public:
	Chat(sf::RenderWindow& window);
	sf::RectangleShape& getOuterScrollBar();
	sf::RectangleShape& getInnerScrollBar();
	sf::RectangleShape& getChatTextBox();
	sf::RectangleShape& getUserTextBox();
	std::vector<std::unique_ptr<chatStrings>>& getStrVector();
	sf::Font& getFont();
	sfe::RichText& getChatText();
	sfe::RichText& getUserText();
private:
	sf::RectangleShape outerScrollBar, innerScrollBar, chatTextBox, userTextBox;
	sf::Color grayColor;
	std::vector<std::unique_ptr<chatStrings>> strVector;
	sf::Font font;
	sfe::RichText chatText, userText;
};

void addString(GameVariables* gv, Chat& chat);

void moveUp(GameVariables* gv, Chat& chat);

void moveDown(GameVariables* gv, Chat& chat);