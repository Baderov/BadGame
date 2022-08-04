#include "Chat.h" // header file for working with chat.

const int SINGLE_LINE_WIDTH = 54;
const int TWO_LINE_WIDTH = 109;
const int THREE_LINE_WIDTH = 164;
const int FOUR_LINE_WIDTH = 202;
const int NUM_OF_DISPLAYED_ROWS = 10;

Chat::Chat(sf::RenderWindow& window) // chat constructor.
{
	greyColor.r = 120;
	greyColor.g = 120;
	greyColor.b = 120;

	chatTextBox.setSize(sf::Vector2f(509.f, 222.f));
	chatTextBox.setFillColor(sf::Color(0, 0, 0, 100));
	chatTextBox.setPosition(50.f, window.getSize().y / 2.f + chatTextBox.getSize().y / 2.f);
	chatTextBox.setOutlineThickness(2.f);
	chatTextBox.setOutlineColor(sf::Color::Black);

	userTextBox.setSize(sf::Vector2f(chatTextBox.getSize().x, 100.f));
	userTextBox.setFillColor(sf::Color(0, 0, 0, 100));
	userTextBox.setPosition(chatTextBox.getPosition().x, (chatTextBox.getPosition().y + chatTextBox.getSize().y) + 2.f);
	userTextBox.setOutlineThickness(2.f);
	userTextBox.setOutlineColor(sf::Color::Black);

	font.loadFromFile("consolab.ttf");
	chatText.setFont(font);
	chatText.setCharacterSize(17);
	chatText.setPosition(chatTextBox.getPosition().x + 10.f, chatTextBox.getPosition().y + 7.f);

	userText.setFont(font);
	userText.setCharacterSize(17);
	userText.setPosition(userTextBox.getPosition().x + 10.f, userTextBox.getPosition().y + 7.f);

	outerScrollBar.setSize(sf::Vector2f(30.f, chatTextBox.getSize().y + userTextBox.getSize().y + 2.f));
	outerScrollBar.setFillColor(sf::Color(0, 0, 0, 100));
	outerScrollBar.setOrigin(outerScrollBar.getSize() / 2.f);
	outerScrollBar.setPosition((chatTextBox.getPosition().x + chatTextBox.getSize().x + (outerScrollBar.getSize().x / 2.f)) + 2.f, (chatTextBox.getPosition().y + (outerScrollBar.getSize().y / 2.f)));
	outerScrollBar.setOutlineThickness(2.f);
	outerScrollBar.setOutlineColor(sf::Color::Black);

	innerScrollBar.setSize(sf::Vector2f(0, 0));
	innerScrollBar.setFillColor(sf::Color::White);
	innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
	innerScrollBar.setPosition(outerScrollBar.getPosition());
	innerScrollBar.setOutlineThickness(1.f);
	innerScrollBar.setOutlineColor(sf::Color::Black);
}

sf::RectangleShape& Chat::getOuterScrollBar() // function to get outer scrollbar.
{
	return outerScrollBar;
}
sf::RectangleShape& Chat::getInnerScrollBar() // function to get inner scrollbar.
{
	return innerScrollBar;
}
sf::RectangleShape& Chat::getChatTextBox() // function to get chat textbox.
{
	return chatTextBox;
}
sf::RectangleShape& Chat::getUserTextBox() // function to get user textbox.
{
	return userTextBox;
}
std::vector<std::unique_ptr<Chat::chatStrings>>& Chat::getStrVector() // function to get string vector.
{
	return strVector;
}
sf::Font& Chat::getFont() // function to get font.
{
	return font;
}
sfe::RichText& Chat::getChatText() // function to get chat text.
{
	return chatText;
}
sfe::RichText& Chat::getUserText() // function to get user text.
{
	return userText;
}

void Chat::addString(GameVariables* gv, Chat& chat) // function to add a string to a vector.
{
	std::wstring tempStr = L"";
	size_t subStrStep = SINGLE_LINE_WIDTH - gv->chatPrefix.size(), max = 0, min = 0;
	if (gv->chatStr != L"" && gv->chatStr.size() <= FOUR_LINE_WIDTH)
	{
		gv->chatStr.erase(std::remove(gv->chatStr.begin(), gv->chatStr.end(), '\n'), gv->chatStr.end());
		if (gv->joinToServer == true && gv->leftFromServer == false)
		{
			chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, gv->joinedMsg, 1, true, false));
		}
		
		else if (gv->leftFromServer == true && gv->joinToServer == false)
		{
			chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, gv->leftMsg, 1, false, true));
		}
		else
		{
			for (size_t i = 0; i < gv->numOfLinesInChat; i++)
			{
				if (i == 0)
				{
					tempStr = gv->chatStr.substr(0, subStrStep);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 1, false, false));
					if (gv->numOfLinesInChat == 1 && gv->chatStr.size() > subStrStep)
					{
						tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
						chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 2, false, false));
					}
				}
				else if (i == 1)
				{
					tempStr = gv->chatStr.substr(subStrStep, SINGLE_LINE_WIDTH);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 2, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->numOfLinesInChat == 2 && gv->chatStr.size() > subStrStep)
					{
						tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
						chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 3, false, false));
					}

				}
				else if (i == 2)
				{
					tempStr = gv->chatStr.substr(subStrStep, SINGLE_LINE_WIDTH);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 3, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->numOfLinesInChat == 3 && gv->chatStr.size() > subStrStep)
					{
						tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
						chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 4, false, false));
					}

				}
				else if (i == 3)
				{
					tempStr = gv->chatStr.substr(subStrStep, SINGLE_LINE_WIDTH);
					chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 4, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->numOfLinesInChat == 4 && gv->chatStr.size() > subStrStep)
					{
						tempStr = gv->chatStr.substr(subStrStep, gv->chatStr.size() - subStrStep);
						chat.getStrVector().emplace_back(new chatStrings(gv->chatPrefix, tempStr, 5, false, false));
					}
				}
			}
		}

		chat.getChatText().clear();
		max = chat.getStrVector().size() - gv->scrollbarStepNumber;
		if (max > NUM_OF_DISPLAYED_ROWS)
		{
			min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (chat.getStrVector()[min].get()->joinedTheServer == true && chat.getStrVector()[min].get()->leftTheServer == false)
				{
					chat.getChatText() << sf::Color::Green << chat.getStrVector()[min].get()->msg << '\n';
				}
				else if (chat.getStrVector()[min].get()->leftTheServer == true && chat.getStrVector()[min].get()->joinedTheServer == false)
				{
					chat.getChatText() << sf::Color::Red << chat.getStrVector()[min].get()->msg << '\n';
				}
				else
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

			if (gv->scrollbarStepNumber >= 0)
			{
				gv->scrollbarStepNumber = 0;

				gv->scrollbarDivisor = static_cast<float>(chat.getStrVector().size()) - 9.f;
				if (gv->scrollbarDivisor <= 0.f) { gv->scrollbarDivisor = 1.f; }

				chat.getInnerScrollBar().setSize(sf::Vector2f(30.f, chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
				chat.getInnerScrollBar().setOrigin(chat.getInnerScrollBar().getSize() / 2.f);
				chat.getInnerScrollBar().setPosition(chat.getOuterScrollBar().getPosition().x, (chat.getOuterScrollBar().getPosition().y + chat.getOuterScrollBar().getSize().y / 2.f) - chat.getInnerScrollBar().getSize().y / 2.f);
				chat.getChatText().clear();
				max = chat.getStrVector().size() - gv->scrollbarStepNumber;
				min = max - NUM_OF_DISPLAYED_ROWS;
				for (; min < max; min++)
				{
					if (chat.getStrVector()[min].get()->joinedTheServer == true && chat.getStrVector()[min].get()->leftTheServer == false)
					{
						chat.getChatText() << sf::Color::Green << chat.getStrVector()[min].get()->msg << '\n';
					}
					else if (chat.getStrVector()[min].get()->leftTheServer == true && chat.getStrVector()[min].get()->joinedTheServer == false)
					{
						chat.getChatText() << sf::Color::Red << chat.getStrVector()[min].get()->msg << '\n';
					}
					else
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
			}
		}
		else
		{
			chat.getChatText().clear();
			for (size_t a = 0; a < chat.getStrVector().size(); a++)
			{
				if (chat.getStrVector()[a].get()->joinedTheServer == true && chat.getStrVector()[a].get()->leftTheServer == false)
				{
					chat.getChatText() << sf::Color::Green << chat.getStrVector()[a].get()->msg << '\n';
				}
				else if (chat.getStrVector()[a].get()->leftTheServer == true && chat.getStrVector()[a].get()->joinedTheServer == false)
				{
					chat.getChatText() << sf::Color::Red << chat.getStrVector()[a].get()->msg << '\n';
				}
				else
				{
					if (chat.getStrVector()[a].get()->countOfLines == 1)
					{
						chat.getChatText() << sf::Color::Cyan << chat.getStrVector()[a].get()->prefix << sf::Color::White << chat.getStrVector()[a].get()->msg << '\n';
					}
					else
					{
						chat.getChatText() << sf::Color::White << chat.getStrVector()[a].get()->msg << '\n';
					}
				}
			}
		}
	}
}

void Chat::addEndLine(GameVariables* gv, Chat& chat) // function to add the end of the line.
{
	if (gv->userStr.size() == SINGLE_LINE_WIDTH || gv->userStr.size() == TWO_LINE_WIDTH || gv->userStr.size() == THREE_LINE_WIDTH)
	{
		gv->userStr += '\n';
		chat.getUserText().clear();
		chat.getUserText() << sf::Color::Black << gv->userStr;
		gv->numOfLinesInUserTextBox++;
	}
}

void Chat::scrollUp(GameVariables* gv, Chat& chat) // function to scroll up the chat.
{
	chat.getInnerScrollBar().move(0.f, -(chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
	if (chat.getStrVector().size() > gv->scrollbarStepNumber)
	{
		if (chat.getStrVector().size() - gv->scrollbarStepNumber > NUM_OF_DISPLAYED_ROWS)
		{
			gv->scrollbarStepNumber++;
		}
		size_t max = chat.getStrVector().size() - gv->scrollbarStepNumber;
		if (max >= NUM_OF_DISPLAYED_ROWS)
		{
			chat.getChatText().clear();
			size_t min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (chat.getStrVector()[min].get()->joinedTheServer == true && chat.getStrVector()[min].get()->leftTheServer == false)
				{
					chat.getChatText() << sf::Color::Green << chat.getStrVector()[min].get()->msg << '\n';
				}
				else if (chat.getStrVector()[min].get()->leftTheServer == true && chat.getStrVector()[min].get()->joinedTheServer == false)
				{
					chat.getChatText() << sf::Color::Red << chat.getStrVector()[min].get()->msg << '\n';
				}
				else
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
		}
	}
}

void Chat::scrollDown(GameVariables* gv, Chat& chat) // function to scroll down the chat.
{
	chat.getInnerScrollBar().move(0.f, (chat.getOuterScrollBar().getSize().y / gv->scrollbarDivisor));
	if (gv->scrollbarStepNumber > 0)
	{
		if (chat.getStrVector().size() > NUM_OF_DISPLAYED_ROWS)
		{
			gv->scrollbarStepNumber--;
		}
		size_t max = chat.getStrVector().size() - gv->scrollbarStepNumber;
		if (max >= NUM_OF_DISPLAYED_ROWS)
		{
			chat.getChatText().clear();
			size_t min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (chat.getStrVector()[min].get()->joinedTheServer == true && chat.getStrVector()[min].get()->leftTheServer == false)
				{
					chat.getChatText() << sf::Color::Green << chat.getStrVector()[min].get()->msg << '\n';
				}
				else if (chat.getStrVector()[min].get()->leftTheServer == true && chat.getStrVector()[min].get()->joinedTheServer == false)
				{
					chat.getChatText() << sf::Color::Red << chat.getStrVector()[min].get()->msg << '\n';
				}
				else
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
		}
	}
}

bool Chat::trimString(std::wstring& str, GameVariables* gv) // string trim function.
{
	// checking for a string of spaces.
	for (size_t i = 0; i < str.size();)
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			i++;
		}
		else
		{
			break;
		}
		if (i == str.size())
		{
			return false;
		}
	}
	// checking for spaces at the beginning of the string.
	size_t subStrPos = 0;
	while (str[subStrPos] == ' ' || str[subStrPos] == '\n')
	{
		subStrPos++;
	}
	str = str.substr(subStrPos, str.size() - subStrPos);

	// checking for spaces at the end of the string.
	for (size_t i = str.size() - 1; i > 0; i--)
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			str.resize(str.size() - 1);
		}
		else
		{
			break;
		}
	}


	if (str.size() > 0 && str.size() <= SINGLE_LINE_WIDTH)
	{
		gv->numOfLinesInUserTextBox = 1;
	}
	else if (str.size() > SINGLE_LINE_WIDTH && str.size() <= TWO_LINE_WIDTH)
	{
		gv->numOfLinesInUserTextBox = 2;
	}
	else if (str.size() > TWO_LINE_WIDTH && str.size() <= THREE_LINE_WIDTH)
	{
		gv->numOfLinesInUserTextBox = 3;
	}
	else if (str.size() > THREE_LINE_WIDTH && str.size() < FOUR_LINE_WIDTH)
	{
		gv->numOfLinesInUserTextBox = 4;
	}
	return true;
}