#include "pch.h"
#include "PlayersList.h"

void PlayersList::init()
{
	setScrollbarStepNumber(0);
	setScrollbarDivisor(1.f);
	setScrollbarDir(L"");

	setScrollbarYPos(0);
	getFont().loadFromFile("consolas.ttf");
	getRS().setSize(sf::Vector2f(700.f, 730.f));
	getRS().setFillColor(sf::Color(0, 0, 0, 100));
	getRS().setOrigin(getRS().getSize() / 2.f);
	getRS().setPosition(50.f, 200.f + getRS().getSize().y / 2.f);
	getRS().setOutlineThickness(2.f);
	getRS().setOutlineColor(sf::Color::Black);

	getOuterScrollBar().setSize(sf::Vector2f(30.f, getRS().getSize().y));
	getOuterScrollBar().setFillColor(sf::Color(0, 0, 0, 100));
	getOuterScrollBar().setOrigin(getOuterScrollBar().getSize() / 2.f);
	getOuterScrollBar().setPosition((getRS().getPosition().x + (getRS().getSize().x / 2.f) + (getOuterScrollBar().getSize().x / 2.f)) + 2.f, getRS().getPosition().y);
	getOuterScrollBar().setOutlineThickness(2.f);
	getOuterScrollBar().setOutlineColor(sf::Color::Black);

	getInnerScrollBar().setSize(sf::Vector2f(0, 0));
	getInnerScrollBar().setFillColor(sf::Color::White);
	getInnerScrollBar().setOrigin(getInnerScrollBar().getSize() / 2.f);
	getInnerScrollBar().setPosition(getOuterScrollBar().getPosition());
	getInnerScrollBar().setOutlineThickness(1.f);
	getInnerScrollBar().setOutlineColor(sf::Color::Black);

	getText().setFont(getFont());
	getText().setCharacterSize(50);
	getText().setFillColor(sf::Color::Cyan);

	setShowPlayersList(false);
	setPLContainsMouse(false);
}

PlayersList::PlayersList() { init(); }

void PlayersList::update(std::unique_ptr<GameVariable>& gv)
{
	PLContainsMouseCheck(gv);
	updateRSPos(gv);
	updateText(gv);
	updateScrollbarDir();
}

void PlayersList::draw(std::unique_ptr<GameVariable>& gv)
{
	if (getShowPlayersList())
	{
		gv->window.draw(getOuterScrollBar());
		gv->window.draw(getInnerScrollBar());
		gv->window.draw(getRS());
		gv->window.draw(getText());
	}
}

void PlayersList::PLContainsMouseCheck(std::unique_ptr<GameVariable>& gv)
{
	if (getRS().getGlobalBounds().contains(gv->getMousePos()) || getOuterScrollBar().getGlobalBounds().contains(gv->getMousePos()) || getInnerScrollBar().getGlobalBounds().contains(gv->getMousePos()))
	{
		setPLContainsMouse(true);
	}
	else { setPLContainsMouse(false); }
}

void PlayersList::scrollUp()
{
	setScrollbarYPos(getScrollbarYPos() + std::round(-(getOuterScrollBar().getSize().y / getScrollbarDivisor())));
	if ((clientVec.size() > getScrollbarStepNumber()) && (clientVec.size() - getScrollbarStepNumber() > NUM_OF_DISPLAYED_PLAYERS)) { setScrollbarStepNumber(getScrollbarStepNumber() + 1); }
	setScrollbarDir(L"");
}

void PlayersList::scrollDown()
{
	setScrollbarYPos(getScrollbarYPos() + std::round(getOuterScrollBar().getSize().y / getScrollbarDivisor()));
	if (getScrollbarStepNumber() > 0 && clientVec.size() > NUM_OF_DISPLAYED_PLAYERS) { setScrollbarStepNumber(getScrollbarStepNumber() - 1); }
	setScrollbarDir(L"");
}

void PlayersList::updateScrollbar()
{
	setScrollbarStepNumber(0);
	setScrollbarYPos(0);
}

void PlayersList::updateRSPos(std::unique_ptr<GameVariable>& gv)
{
	getRS().setPosition(gv->getGameViewCenter());
	getOuterScrollBar().setPosition((getRS().getPosition().x + (getRS().getSize().x / 2.f) + (getOuterScrollBar().getSize().x / 2.f)) + 2.f, getRS().getPosition().y);
	getInnerScrollBar().setPosition(getOuterScrollBar().getPosition());
}

void PlayersList::updateText(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getGameLanguage() == 'e') { getText().setString(L"	 PLAYERS ONLINE\nNICKNAME			PING\n"); }
	else if (gv->getGameLanguage() == 'r') { getText().setString(L"	 ÈÃÐÎÊÈ ÎÍËÀÉÍ\nÍÈÊÍÅÉÌ			ÏÈÍÃ\n"); }
	size_t current = 0;
	size_t max = clientVec.size() - getScrollbarStepNumber();
	size_t numOfPasses = 0;
	if (max >= NUM_OF_DISPLAYED_PLAYERS)
	{
		if (getScrollbarStepNumber() >= 0)
		{
			setScrollbarDivisor(static_cast<float>(clientVec.size()) - 9.f);
			if (getScrollbarDivisor() <= 0.f) { setScrollbarDivisor(1.f); }
			getInnerScrollBar().setSize(sf::Vector2f(30.f, std::round(getOuterScrollBar().getSize().y / getScrollbarDivisor())));
			getInnerScrollBar().setOrigin(getInnerScrollBar().getSize() / 2.f);
			getInnerScrollBar().setPosition(getOuterScrollBar().getPosition().x, std::round((((getOuterScrollBar().getPosition().y + getOuterScrollBar().getSize().y / 2.f) - getInnerScrollBar().getSize().y / 2.f) + getScrollbarYPos())));
		}
		current = max - NUM_OF_DISPLAYED_PLAYERS;
		numOfPasses = current;
	}

	for (auto& client : clientVec)
	{
		if (client == nullptr) { continue; }
		if (current >= max) { break; }
		if (numOfPasses > 0) { numOfPasses--; continue; }

		std::wstring tab = L"";
		size_t tabSize = 20 - client->getName().size();
		tab.append(tabSize, ' ');
		getText().setString(getText().getString() + client->getName() + tab + std::to_wstring(client->getPing()) + '\n');
		++current;
	}

	getText().setPosition(getRS().getPosition().x - 325.f, (getRS().getPosition().y - (getRS().getSize().y / 2.f)));
}

void PlayersList::updateScrollbarDir()
{
	if (getScrollbarDir() == L"up" && ((getInnerScrollBar().getPosition().y - (getInnerScrollBar().getSize().y / 2.f))) > getOuterScrollBar().getPosition().y - (getOuterScrollBar().getSize().y / 2.f))
	{
		scrollUp();
	}
	else if (getScrollbarDir() == L"down" && ((getInnerScrollBar().getPosition().y + (getInnerScrollBar().getSize().y / 2.f))) < getOuterScrollBar().getPosition().y + (getOuterScrollBar().getSize().y / 2.f))
	{
		scrollDown();
	}
}

void PlayersList::setScrollbarYPos(float tempScrollbarYPos) { scrollbarYPos = std::move(tempScrollbarYPos); }
void PlayersList::setScrollbarDivisor(float tempScrollbarDivisor) { scrollbarDivisor = std::move(tempScrollbarDivisor); }
void PlayersList::setShowPlayersList(bool tempShowPlayersList) { showPlayersList = std::move(tempShowPlayersList); }
void PlayersList::setPLContainsMouse(bool tempPLContainsMouse) { PLContainsMouse = std::move(tempPLContainsMouse); }
void PlayersList::setScrollbarDir(std::wstring tempScrollbarDir) { scrollbarDir = std::move(tempScrollbarDir); }
void PlayersList::setScrollbarStepNumber(size_t tempScrollbarStepNumber) { scrollbarStepNumber = std::move(tempScrollbarStepNumber); }

float& PlayersList::getScrollbarYPos() { return scrollbarYPos; }
float& PlayersList::getScrollbarDivisor() { return scrollbarDivisor; }
bool& PlayersList::getShowPlayersList() { return showPlayersList; }
bool& PlayersList::getPLContainsMouse() { return PLContainsMouse; }
std::wstring& PlayersList::getScrollbarDir() { return scrollbarDir; }
size_t& PlayersList::getScrollbarStepNumber() { return scrollbarStepNumber; }
sf::RectangleShape& PlayersList::getRS() { return RS; }
sf::RectangleShape& PlayersList::getOuterScrollBar() { return outerScrollBar; }
sf::RectangleShape& PlayersList::getInnerScrollBar() { return innerScrollBar; }
sf::Text& PlayersList::getText() { return text; }
sf::Font& PlayersList::getFont() { return font; }