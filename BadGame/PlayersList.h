#pragma once
#include "Clients.h"

const size_t NUM_OF_DISPLAYED_PLAYERS = 10;

class PlayersList
{
public:
	PlayersList();
	void updateRSPos(float x, float y);
	void updateText(GameVariable* gv, int numOfClients);
	void updateScrollbarDir(int numOfClients);
	void scrollUp(int numOfClients);
	void scrollDown(int numOfClients);
	void updatePL(GameVariable* gv, int numOfClients);
	void updatePLScrollbar();
	void setScrollbarDir(std::wstring tempScrollbarDir);
	size_t getScrollbarStepNumber();

	size_t scrollbarStepNumber;
	float scrollbarDivisor;
	float scrollbarYPos;
	std::wstring scrollbarDir;

	sf::RectangleShape RS, outerScrollBar, innerScrollBar;
	sf::Font font;
	sf::Text text;
};