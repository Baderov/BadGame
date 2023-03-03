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

void PlayersList::updateText(GameVariable* gv, std::vector<std::unique_ptr<Clients>>& clientsVec)
{
	size_t max = clientsVec.size() - scrollbarStepNumber;
	if (max >= NUM_OF_DISPLAYED_PLAYERS)
	{
		if (scrollbarStepNumber >= 0)
		{
			scrollbarDivisor = static_cast<float>(clientsVec.size()) - 9.f;
			if (scrollbarDivisor <= 0.f) { scrollbarDivisor = 1.f; }
			innerScrollBar.setSize(sf::Vector2f(30.f, std::round(outerScrollBar.getSize().y / scrollbarDivisor)));
			innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
			innerScrollBar.setPosition(outerScrollBar.getPosition().x, std::round((((outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - innerScrollBar.getSize().y / 2.f) + scrollbarYPos)));
		}

		size_t current = max - NUM_OF_DISPLAYED_PLAYERS;
		if (gv->getGameLanguage() == 'e')
		{
			text.setString(L"	 PLAYERS ONLINE\nNICKNAME			PING\n");
		}
		else if (gv->getGameLanguage() == 'r')
		{
			text.setString(L"	 »√–Œ » ŒÕÀ¿…Õ\nÕ» Õ≈…Ã			œ»Õ√\n");
		}
		for (; current < max; current++)
		{
			std::wstring tab = L"";
			size_t tabSize = 20 - clientsVec[current]->getNickname().size();
			tab.append(tabSize, ' ');
			text.setString(text.getString() + clientsVec[current]->getNickname() + tab + std::to_wstring(clientsVec[current]->getPing()) + '\n');
		}
	}
	else
	{
		size_t current = 0;
		if (gv->getGameLanguage() == 'e')
		{
			text.setString(L"	 PLAYERS ONLINE\nNICKNAME			PING\n");
		}
		else if (gv->getGameLanguage() == 'r')
		{
			text.setString(L"	 »√–Œ » ŒÕÀ¿…Õ\nÕ» Õ≈…Ã			œ»Õ√\n");
		}
		for (; current < max; current++)
		{
			std::wstring tab = L"";
			size_t tabSize = 20 - clientsVec[current]->getNickname().size();
			tab.append(tabSize, ' ');
			text.setString(text.getString() + clientsVec[current]->getNickname() + tab + std::to_wstring(clientsVec[current]->getPing()) + '\n');
		}
	}
	text.setPosition(RS.getPosition().x - 325.f, (RS.getPosition().y - (RS.getSize().y / 2.f)));
}

void PlayersList::updateScrollbarDir(size_t clientsVecSize)
{
	if (scrollbarDir == L"up" && ((innerScrollBar.getPosition().y - (innerScrollBar.getSize().y / 2.f))) > outerScrollBar.getPosition().y - (outerScrollBar.getSize().y / 2.f))
	{
		scrollUp(clientsVecSize);
	}
	else if (scrollbarDir == L"down" && ((innerScrollBar.getPosition().y + (innerScrollBar.getSize().y / 2.f))) < outerScrollBar.getPosition().y + (outerScrollBar.getSize().y / 2.f))
	{
		scrollDown(clientsVecSize);
	}
}

void PlayersList::scrollUp(size_t clientsVecSize)
{
	scrollbarYPos += std::round(-(outerScrollBar.getSize().y / scrollbarDivisor));
	if ((clientsVecSize > scrollbarStepNumber) && (clientsVecSize - scrollbarStepNumber > NUM_OF_DISPLAYED_PLAYERS)) { scrollbarStepNumber++; }
	scrollbarDir = L"";
}

void PlayersList::scrollDown(size_t clientsVecSize)
{
	scrollbarYPos += std::round(outerScrollBar.getSize().y / scrollbarDivisor);
	if (scrollbarStepNumber > 0 && clientsVecSize > NUM_OF_DISPLAYED_PLAYERS) { scrollbarStepNumber--; }
	scrollbarDir = L"";
}

void PlayersList::updatePL(GameVariable* gv, std::mutex& cVec_mtx, std::vector<std::unique_ptr<Clients>>& clientsVec)
{
	cVec_mtx.lock();
	PL_mtx.lock();

	updateRSPos(getCurrentClientPos().x, getCurrentClientPos().y);
	updateText(gv, clientsVec);
	updateScrollbarDir(clientsVec.size());

	PL_mtx.unlock();
	cVec_mtx.unlock();
}

void PlayersList::updatePLScrollbar()
{
	PL_mtx.lock();

	scrollbarStepNumber = 0;
	scrollbarYPos = 0;

	PL_mtx.unlock();
}

void PlayersList::setScrollbarDir(std::wstring tempScrollbarDir)
{
	PL_mtx.lock();
	scrollbarDir = tempScrollbarDir;
	PL_mtx.unlock();
}

size_t PlayersList::getScrollbarStepNumber()
{
	PL_mtx.lock();
	size_t tempStepNumber = scrollbarStepNumber;
	PL_mtx.unlock();
	return tempStepNumber;
}
