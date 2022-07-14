#include "Chat.h"

Chat::Chat(sf::RenderWindow& window)
{
	grayColor.r = 0;
	grayColor.g = 0;
	grayColor.b = 0;
	grayColor.a = 100;

	chatTextBox.setSize(sf::Vector2f(509.f, 222.f));
	chatTextBox.setFillColor(sf::Color(0, 0, 0, 100));
	chatTextBox.setPosition(50.f, window.getSize().y / 2.f + chatTextBox.getSize().y / 2.f);
	chatTextBox.setOutlineThickness(3.f);
	chatTextBox.setOutlineColor(sf::Color::Black);

	userTextBox.setSize(sf::Vector2f(chatTextBox.getSize().x + 3.f, 100.f));
	userTextBox.setFillColor(sf::Color(255, 255, 255, 180));
	userTextBox.setPosition(chatTextBox.getPosition().x, chatTextBox.getPosition().y + chatTextBox.getSize().y);
	userTextBox.setOutlineThickness(3.f);
	userTextBox.setOutlineColor(sf::Color::Black);

	font.loadFromFile("consolab.ttf");
	chatText.setFont(font);
	chatText.setCharacterSize(17);
	chatText.setPosition(chatTextBox.getPosition().x + 10.f, chatTextBox.getPosition().y + 7.f);

	userText.setFont(font);
	userText.setCharacterSize(17);
	userText.setPosition(userTextBox.getPosition().x + 10.f, userTextBox.getPosition().y + 7.f);

	outerScrollBar.setSize(sf::Vector2f(30.f, chatTextBox.getSize().y + userTextBox.getSize().y));
	outerScrollBar.setFillColor(sf::Color::White);
	outerScrollBar.setOrigin(outerScrollBar.getSize() / 2.f);
	outerScrollBar.setPosition(chatTextBox.getPosition().x + chatTextBox.getSize().x + (outerScrollBar.getSize().x / 2.f), (chatTextBox.getPosition().y + (outerScrollBar.getSize().y / 2.f)));
	outerScrollBar.setOutlineThickness(3.f);
	outerScrollBar.setOutlineColor(sf::Color::Black);

	innerScrollBar.setSize(sf::Vector2f(30.f, outerScrollBar.getSize().y));
	innerScrollBar.setFillColor(grayColor);
	innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
	innerScrollBar.setPosition(outerScrollBar.getPosition());
	innerScrollBar.setOutlineThickness(1.f);
	innerScrollBar.setOutlineColor(sf::Color::Black);
}

sf::RectangleShape& Chat::getOuterScrollBar()
{
	return outerScrollBar;
}
sf::RectangleShape& Chat::getInnerScrollBar()
{
	return innerScrollBar;
}
sf::RectangleShape& Chat::getChatTextBox()
{
	return chatTextBox;
}
sf::RectangleShape& Chat::getUserTextBox()
{
	return userTextBox;
}
std::vector<std::unique_ptr<chatStrings>>& Chat::getStrVector()
{
	return strVector;
}
sf::Font& Chat::getFont()
{
	return font;
}
sfe::RichText& Chat::getChatText()
{
	return chatText;
}
sfe::RichText& Chat::getUserText()
{
	return userText;
}

void addString(GameVariables *gv, Chat& chat)
{
	std::wstring tempStr = L"";
	int subStrStep = 54 - gv->chatPrefix.size();
	if (gv->chatStr != L"" && gv->chatStr.size() <= 202)
	{
		gv->chatStr.erase(std::remove(gv->chatStr.begin(), gv->chatStr.end(), '\n'), gv->chatStr.end());
		for (int i = 0; i < gv->numOfLinesInChat; i++)
		{
			if (i == 0)
			{
				tempStr = gv->chatStr.substr(0, subStrStep);
				chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 1));
				if (gv->numOfLinesInChat == 1 && gv->chatStr.size() > subStrStep) 
				{
					tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 2));
				}
			}
			else if (i == 1)
			{
				tempStr = gv->chatStr.substr(subStrStep, 54);
				chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 2));
				subStrStep += 54;
				if (gv->numOfLinesInChat == 2 && gv->chatStr.size() > subStrStep)
				{
					tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 3));
				}

			}
			else if (i == 2)
			{
				tempStr = gv->chatStr.substr(subStrStep, 54);
				chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 3));
				subStrStep += 54;
				if (gv->numOfLinesInChat == 3 && gv->chatStr.size() > subStrStep) 
				{
					tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 4));
				}

			}
			else if (i == 3)
			{
				tempStr = gv->chatStr.substr(subStrStep, 54);
				chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 4));
				subStrStep += 54;
				if (gv->numOfLinesInChat == 4 && gv->chatStr.size() > subStrStep) 
				{
					tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 5));
				}
			}

			chat.getChatText().clear();
			unsigned int max = chat.getStrVector().size() - gv->scrollbarStepNumber;
			if (max > 10)
			{
			/*	unsigned int min = max - 10;
				for (; min < max; min++)
				{
					if (chat.getStrVector()[min].get()->countOfLines == 1)
					{
						chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[min].get()->prefix << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
					}
					else
					{
						chat.getChatText() << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
					}
				}
				if (gv->scrollbarStepNumber >= 0)
				{
					gv->scrollbarStepNumber = 0;
					gv->scrollbarDivisor = chat.getStrVector().size() - 9;
					if (gv->scrollbarDivisor <= 0) { gv->scrollbarDivisor = 1; }

					chat.getInnerScrollBar().setSize(sf::Vector2f(30.f, chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
					chat.getInnerScrollBar().setOrigin(chat.getInnerScrollBar().getSize() / 2.f);
					chat.getInnerScrollBar().setPosition(chat.getOuterScrollBar().getPosition().x, (chat.getOuterScrollBar().getPosition().y + chat.getOuterScrollBar().getSize().y / 2.f) - chat.getInnerScrollBar().getSize().y / 2.f);
					chat.getChatText().clear();
					unsigned int max = chat.getStrVector().size() - gv->scrollbarStepNumber;
					unsigned int min = max - 10;
					for (; min < max; min++)
					{
						if (chat.getStrVector()[min].get()->countOfLines == 1)
						{
							chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[min].get()->prefix << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
						}
						else
						{
							chat.getChatText() << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
						}
					}
				}*/
			}
			else
			{
				chat.getChatText().clear();
				for (int a = 0; a < chat.getStrVector().size(); a++)
				{
					if (chat.getStrVector()[a].get()->countOfLines == 1)
					{
						chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[a].get()->prefix << sf::Color::White << chat.getStrVector()[a].get()->msg << '\n';
					}
				/*	else
					{
						chat.getChatText() << sf::Color::White << chat.getStrVector()[a].get()->msg << '\n';
					}*/
				}
			}
		}
	}
}

void moveUp(GameVariables* gv, Chat& chat)
{
	/*chat.getInnerScrollBar().move(0.f, -(chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
	if (chat.getStrVector().size() > gv->scrollbarStepNumber)
	{
		if (chat.getStrVector().size() - gv->scrollbarStepNumber > 10)
		{
			gv->scrollbarStepNumber++;
		}
		unsigned int max = chat.getStrVector().size() - gv->scrollbarStepNumber;
		if (max >= 10)
		{
			chat.getChatText().clear();
			unsigned int min = max - 10;
			for (; min < max; min++)
			{
				if (chat.getStrVector()[min].get()->countOfLines == 1)
				{
					chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[min].get()->prefix << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
				}
				else
				{
					chat.getChatText() << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
				}
			}
		}
	}*/
}

void moveDown(GameVariables* gv, Chat& chat)
{
	/*chat.getInnerScrollBar().move(0.f, (chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
	if (gv->scrollbarStepNumber > 0)
	{
		if (chat.getStrVector().size() > 10)
		{
			gv->scrollbarStepNumber--;
		}
		unsigned int max = chat.getStrVector().size() - gv->scrollbarStepNumber;
		if (max >= 10)
		{
			chat.getChatText().clear();
			unsigned int min = max - 10;
			for (; min < max; min++)
			{
				if (chat.getStrVector()[min].get()->countOfLines == 1)
				{
					chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[min].get()->prefix << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
				}
				else
				{
					chat.getChatText() << sf::Color::White << chat.getStrVector()[min].get()->msg << '\n';
				}
			}
		}
	}*/
}