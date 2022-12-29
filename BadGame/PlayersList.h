#pragma once
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <iostream> // header that defines the standard input/output stream objects.
#include <mutex>
#include "Clients.h"

const size_t NUM_OF_DISPLAYED_PLAYERS = 10;

class PlayersList
{
public:
	PlayersList();
	void updateRSPos(float x, float y);
	void updateText(GameVariable* gv, std::vector<std::unique_ptr<Clients>>& clientsVec);
	void updateScrollbarDir(std::vector<std::unique_ptr<Clients>>& clientsVec);
	void scrollUp(std::vector<std::unique_ptr<Clients>>& clientsVec);
	void scrollDown(std::vector<std::unique_ptr<Clients>>& clientsVec);
	void updatePL(GameVariable* gv, std::mutex& cVec_mtx, std::vector<std::unique_ptr<Clients>>& clientsVec);
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
	std::mutex PL_mtx;
};

