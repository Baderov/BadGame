#include "pch.h"
#include "PlayersList.h"

PlayersList::PlayersList()
{
	scrollbarStepNumber = 0;
	scrollbarDivisor = 1.f;
	scrollbarDir = L"";
	scrollbarYPos = (outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - (innerScrollBar.getSize().y / 2.f);

	font.loadFromFile("consolas.ttf");
	RS.setSize(sf::Vector2f(700.f, 730.f));
	RS.setFillColor(sf::Color(0, 0, 0, 100));
	RS.setOrigin(RS.getSize() / 2.f);
	RS.setPosition(50.f, 200.f + RS.getSize().y / 2.f);
	RS.setOutlineThickness(2.f);
	RS.setOutlineColor(sf::Color::Black);

	outerScrollBar.setSize(sf::Vector2f(30.f, RS.getSize().y));
	outerScrollBar.setFillColor(sf::Color(0, 0, 0, 100));
	outerScrollBar.setOrigin(outerScrollBar.getSize() / 2.f);
	outerScrollBar.setPosition((RS.getPosition().x + (RS.getSize().x / 2.f) + (outerScrollBar.getSize().x / 2.f)) + 2.f, RS.getPosition().y);
	outerScrollBar.setOutlineThickness(2.f);
	outerScrollBar.setOutlineColor(sf::Color::Black);

	innerScrollBar.setSize(sf::Vector2f(0, 0));
	innerScrollBar.setFillColor(sf::Color::White);
	innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
	innerScrollBar.setPosition(outerScrollBar.getPosition());
	innerScrollBar.setOutlineThickness(1.f);
	innerScrollBar.setOutlineColor(sf::Color::Black);

	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Cyan);

}

void PlayersList::updateRSPos(float x, float y)
{
	RS.setPosition(x, y);
	outerScrollBar.setPosition((RS.getPosition().x + (RS.getSize().x / 2.f) + (outerScrollBar.getSize().x / 2.f)) + 2.f, RS.getPosition().y);
	innerScrollBar.setPosition(outerScrollBar.getPosition());
}

void PlayersList::updateText(GameVariable* gv, int numOfClients)
{
	if (gv->getGameLanguage() == 'e')
	{
		text.setString(L"	 PLAYERS ONLINE\nNICKNAME			PING\n");
	}
	else if (gv->getGameLanguage() == 'r')
	{
		text.setString(L"	 ÈÃÐÎÊÈ ÎÍËÀÉÍ\nÍÈÊÍÅÉÌ			ÏÈÍÃ\n");
	}

	size_t current = 0;
	size_t max = numOfClients - scrollbarStepNumber; // max = 20 - 0 = 20.
	size_t numOfPasses = 0;
	if (max >= NUM_OF_DISPLAYED_PLAYERS)
	{
		if (scrollbarStepNumber >= 0)
		{
			scrollbarDivisor = static_cast<float>(numOfClients) - 9.f;
			if (scrollbarDivisor <= 0.f) { scrollbarDivisor = 1.f; }
			innerScrollBar.setSize(sf::Vector2f(30.f, std::round(outerScrollBar.getSize().y / scrollbarDivisor)));
			innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
			innerScrollBar.setPosition(outerScrollBar.getPosition().x, std::round((((outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - innerScrollBar.getSize().y / 2.f) + scrollbarYPos)));
		}
		current = max - NUM_OF_DISPLAYED_PLAYERS; // current = 20 - 10 = 10.
		numOfPasses = current;
	}

	for (auto& entity : gv->entitiesVec)
	{
		if (current >= max) { break; }

		if (entity->getEntityType() == "Client")
		{
			if (numOfPasses > 0) { numOfPasses--; continue; }
			std::wstring tab = L"";
			size_t tabSize = 20 - entity->getName().size();
			tab.append(tabSize, ' ');
			text.setString(text.getString() + entity->getName() + tab + std::to_wstring(entity->getPing()) + '\n');
			current++;
		}
	}

	text.setPosition(RS.getPosition().x - 325.f, (RS.getPosition().y - (RS.getSize().y / 2.f)));
}

void PlayersList::updateScrollbarDir(int numOfClients)
{
	if (scrollbarDir == L"up" && ((innerScrollBar.getPosition().y - (innerScrollBar.getSize().y / 2.f))) > outerScrollBar.getPosition().y - (outerScrollBar.getSize().y / 2.f))
	{
		scrollUp(numOfClients);
	}
	else if (scrollbarDir == L"down" && ((innerScrollBar.getPosition().y + (innerScrollBar.getSize().y / 2.f))) < outerScrollBar.getPosition().y + (outerScrollBar.getSize().y / 2.f))
	{
		scrollDown(numOfClients);
	}
}

void PlayersList::scrollUp(int numOfClients)
{
	scrollbarYPos += std::round(-(outerScrollBar.getSize().y / scrollbarDivisor));
	if ((numOfClients > scrollbarStepNumber) && (numOfClients - scrollbarStepNumber > NUM_OF_DISPLAYED_PLAYERS)) { scrollbarStepNumber++; }
	scrollbarDir = L"";
}

void PlayersList::scrollDown(int numOfClients)
{
	scrollbarYPos += std::round(outerScrollBar.getSize().y / scrollbarDivisor);
	if (scrollbarStepNumber > 0 && numOfClients > NUM_OF_DISPLAYED_PLAYERS) { scrollbarStepNumber--; }
	scrollbarDir = L"";
}

void PlayersList::updatePL(GameVariable* gv, int numOfClients)
{
	updateRSPos(getCurrentClientPos().x, getCurrentClientPos().y);
	updateText(gv, numOfClients);
	updateScrollbarDir(numOfClients);
}

void PlayersList::updatePLScrollbar()
{
	scrollbarStepNumber = 0;
	scrollbarYPos = 0;
}

void PlayersList::setScrollbarDir(std::wstring tempScrollbarDir) { scrollbarDir = tempScrollbarDir; }

size_t PlayersList::getScrollbarStepNumber() { return scrollbarStepNumber; }
