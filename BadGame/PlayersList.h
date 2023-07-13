#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include "Client.h"
#include "ObjectPool.hpp"
#include "Variables.h"

const size_t NUM_OF_DISPLAYED_PLAYERS = 10;

class PlayersList
{
private:
	size_t scrollbarStepNumber;
	float scrollbarDivisor;
	float scrollbarYPos;
	bool showPlayersList;
	bool PLContainsMouse;
	std::wstring scrollbarDir;

	sf::RectangleShape RS, outerScrollBar, innerScrollBar;
	sf::Font font;
	sf::Text text;
	std::mutex mtx;
public:
	PlayersList();

	void init();
	void update(std::unique_ptr<GameVariable>& gv);
	void draw(std::unique_ptr<GameVariable>& gv);

	void PLContainsMouseCheck(std::unique_ptr<GameVariable>& gv);
	void updateRSPos(std::unique_ptr<GameVariable>& gv);
	void updateText(std::unique_ptr<GameVariable>& gv);
	void scrollUp();
	void scrollDown();
	void updateScrollbar();
	void updateScrollbarDir();

	void setScrollbarYPos(float tempScrollbarYPos);
	void setScrollbarDivisor(float tempScrollbarDivisor);
	void setShowPlayersList(bool tempShowPlayersList);
	void setPLContainsMouse(bool tempPLContainsMouse);
	void setScrollbarDir(std::wstring tempScrollbarDir);
	void setScrollbarStepNumber(size_t tempScrollbarStepNumber);

	float& getScrollbarYPos();
	float& getScrollbarDivisor();
	bool& getShowPlayersList();
	bool& getPLContainsMouse();
	std::wstring& getScrollbarDir();
	size_t& getScrollbarStepNumber();

	sf::RectangleShape& getRS();
	sf::RectangleShape& getOuterScrollBar();
	sf::RectangleShape& getInnerScrollBar();
	sf::Text& getText();
	sf::Font& getFont();
};

#endif