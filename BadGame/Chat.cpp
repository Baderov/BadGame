#include "Chat.h" // header file for working with chat.

const int SINGLE_LINE_WIDTH = 54;
const int TWO_LINE_WIDTH = 109;
const int THREE_LINE_WIDTH = 164;
const int FOUR_LINE_WIDTH = 202;
const int NUM_OF_DISPLAYED_ROWS = 10;

Chat::Chat() // chat constructor.
{
	scrollbarDivisor = 1.f;
	scrollbarYPos = (outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - (innerScrollBar.getSize().y / 2.f);
	scrollbarDir = L"";
	scrollbarStepNumber = 0;

	greyColor.r = 120;
	greyColor.g = 120;
	greyColor.b = 120;

	chatTextBox.setSize(sf::Vector2f(509.f, 222.f));
	chatTextBox.setFillColor(sf::Color(0, 0, 0, 100));
	chatTextBox.setPosition(50.f, 200.f + (chatTextBox.getSize().y / 2.f));
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
float Chat::getScrollbarDivisor()
{
	return scrollbarDivisor;
}
size_t Chat::getScrollbarStepNumber()
{
	return scrollbarStepNumber;
}
std::wstring Chat::getScrollbarDir()
{
	return scrollbarDir;
}

void Chat::setOuterScrollBarPos(float posX, float posY)
{
	outerScrollBar.setPosition(posX, posY);
}
void Chat::setInnerScrollBarPos(float posX, float posY)
{
	innerScrollBar.setPosition(posX, posY);
}
void Chat::setChatTextBoxPos(float posX, float posY)
{
	chatTextBox.setPosition(posX, posY);
}
void Chat::setUserTextBoxPos(float posX, float posY)
{
	userTextBox.setPosition(posX, posY);
}
void Chat::setChatTextPos(float posX, float posY)
{
	chatText.setPosition(posX, posY);
}
void Chat::setUserTextPos(float posX, float posY)
{
	userText.setPosition(posX, posY);
}
void Chat::setScrollbarDivisor(float tempDivisor)
{
	scrollbarDivisor = tempDivisor;
}
void Chat::setScrollbarStepNumber(size_t tempStepNumber)
{
	scrollbarStepNumber = tempStepNumber;
}
void Chat::setScrollbarDir(std::wstring tempDir)
{
	scrollbarDir = tempDir;
}

void Chat::addString(GameVariable* gv) // function to add a string to a vector.
{
	chat_mtx.lock();

	std::wstring tempStr = L"";
	size_t subStrStep = SINGLE_LINE_WIDTH - gv->getChatPrefix().size(), max = 0, min = 0;
	if (gv->getChatStr() != L"" && gv->getChatStr().size() <= FOUR_LINE_WIDTH)
	{
		scrollbarYPos = 0;
		scrollbarStepNumber = 0;

		tempStr = gv->getChatStr();
		tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), '\n'), tempStr.end());
		gv->setChatStr(tempStr);
		tempStr = L"";

		if (gv->getJoinToServer() == true && gv->getLeftFromServer() == false)
		{
			strVector.emplace_back(new chatStrings(gv->getChatPrefix(), gv->getJoinedMsg(), 1, true, false));
		}
		else if (gv->getLeftFromServer() == true && gv->getJoinToServer() == false)
		{
			strVector.emplace_back(new chatStrings(gv->getChatPrefix(), gv->getLeftMsg(), 1, false, true));
		}
		else
		{
			for (size_t i = 0; i < gv->getNumOfLinesInChat(); i++)
			{
				if (i == 0)
				{
					tempStr = gv->getChatStr().substr(0, subStrStep);
					strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 1, false, false));
					if (gv->getNumOfLinesInChat() == 1 && gv->getChatStr().size() > subStrStep)
					{
						tempStr = gv->getChatStr().substr(subStrStep, gv->getChatStr().size() - subStrStep);
						strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 2, false, false));
					}
				}
				else if (i == 1)
				{
					tempStr = gv->getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 2, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->getNumOfLinesInChat() == 2 && gv->getChatStr().size() > subStrStep)
					{
						tempStr = gv->getChatStr().substr(subStrStep, gv->getChatStr().size() - subStrStep);
						strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 3, false, false));
					}

				}
				else if (i == 2)
				{
					tempStr = gv->getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 3, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->getNumOfLinesInChat() == 3 && gv->getChatStr().size() > subStrStep)
					{
						tempStr = gv->getChatStr().substr(subStrStep, gv->getChatStr().size() - subStrStep);
						strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 4, false, false));
					}

				}
				else if (i == 3)
				{
					tempStr = gv->getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 4, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (gv->getNumOfLinesInChat() == 4 && gv->getChatStr().size() > subStrStep)
					{
						tempStr = gv->getChatStr().substr(subStrStep, gv->getChatStr().size() - subStrStep);
						strVector.emplace_back(new chatStrings(gv->getChatPrefix(), tempStr, 5, false, false));
					}
				}
			}
		}

		chatText.clear();
		max = strVector.size() - scrollbarStepNumber;
		if (max > NUM_OF_DISPLAYED_ROWS)
		{
			min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (strVector[min]->joinedTheServer == true && strVector[min]->leftTheServer == false)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer == true && strVector[min]->joinedTheServer == false)
				{
					chatText << sf::Color::Red << strVector[min]->msg << '\n';
				}
				else
				{
					if (strVector[min]->countOfLines == 1)
					{
						chatText << sf::Color::Cyan << strVector[min]->prefix << sf::Color::White << strVector[min]->msg << '\n';
					}
					else
					{
						chatText << sf::Color::White << strVector[min]->msg << '\n';
					}
				}
			}

			if (scrollbarStepNumber >= 0)
			{
				scrollbarDivisor = static_cast<float>(strVector.size()) - 9.f;
				if (scrollbarDivisor <= 0.f) { scrollbarDivisor = 1.f; }
				innerScrollBar.setSize(sf::Vector2f(30.f, std::round(outerScrollBar.getSize().y / scrollbarDivisor)));
				innerScrollBar.setOrigin(innerScrollBar.getSize() / 2.f);
				chatText.clear();
				max = strVector.size() - scrollbarStepNumber;
				min = max - NUM_OF_DISPLAYED_ROWS;
				for (; min < max; min++)
				{
					if (strVector[min]->joinedTheServer == true && strVector[min]->leftTheServer == false)
					{
						chatText << sf::Color::Green << strVector[min]->msg << '\n';
					}
					else if (strVector[min]->leftTheServer == true && strVector[min]->joinedTheServer == false)
					{
						chatText << sf::Color::Red << strVector[min]->msg << '\n';
					}
					else
					{
						if (strVector[min]->countOfLines == 1)
						{
							chatText << sf::Color::Cyan << strVector[min]->prefix << sf::Color::White << strVector[min]->msg << '\n';
						}
						else
						{
							chatText << sf::Color::White << strVector[min]->msg << '\n';
						}
					}
				}
			}
		}
		else
		{
			chatText.clear();
			for (size_t a = 0; a < strVector.size(); a++)
			{
				if (strVector[a]->joinedTheServer == true && strVector[a]->leftTheServer == false)
				{
					chatText << sf::Color::Green << strVector[a]->msg << '\n';
				}
				else if (strVector[a]->leftTheServer == true && strVector[a]->joinedTheServer == false)
				{
					chatText << sf::Color::Red << strVector[a]->msg << '\n';
				}
				else
				{
					if (strVector[a]->countOfLines == 1)
					{
						chatText << sf::Color::Cyan << strVector[a]->prefix << sf::Color::White << strVector[a]->msg << '\n';
					}
					else
					{
						chatText << sf::Color::White << strVector[a]->msg << '\n';
					}
				}
			}
		}
	}

	chat_mtx.unlock();
}
void Chat::chatPosUpdate(sf::Vector2f clientPos)
{
	chat_mtx.lock();

	chatTextBox.setPosition(clientPos.x - 750.f, clientPos.y + (chatTextBox.getSize().y / 2.f));
	userTextBox.setPosition(chatTextBox.getPosition().x, (chatTextBox.getPosition().y + chatTextBox.getSize().y) + 2.f);
	chatText.setPosition(chatTextBox.getPosition().x + 10.f, chatTextBox.getPosition().y + 7.f);
	userText.setPosition(userTextBox.getPosition().x + 10.f, userTextBox.getPosition().y + 7.f);
	outerScrollBar.setPosition((chatTextBox.getPosition().x + chatTextBox.getSize().x + (outerScrollBar.getSize().x / 2.f)) + 2.f, (chatTextBox.getPosition().y + (outerScrollBar.getSize().y / 2.f)));
	innerScrollBar.setPosition(outerScrollBar.getPosition().x, std::round(((outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - (innerScrollBar.getSize().y / 2.f)) + scrollbarYPos));

	chat_mtx.unlock();
}
void Chat::addEndLine(GameVariable* gv) // function to add the end of the line.
{
	if (gv->getUserStr().size() == SINGLE_LINE_WIDTH || gv->getUserStr().size() == TWO_LINE_WIDTH || gv->getUserStr().size() == THREE_LINE_WIDTH)
	{
		gv->setUserStr(gv->getUserStr() + L"\n");
		userText.clear();
		userText << sf::Color::Black << gv->getUserStr();
		gv->setNumOfLinesInUserTextBox(gv->getNumOfLinesInUserTextBox() + 1);
	}
}
void Chat::scrollUp(GameVariable* gv) // function to scroll up the chat.
{
	scrollbarYPos += -(outerScrollBar.getSize().y / scrollbarDivisor);
	if (strVector.size() > scrollbarStepNumber)
	{
		if (strVector.size() - scrollbarStepNumber > NUM_OF_DISPLAYED_ROWS) { scrollbarStepNumber++; }
		size_t max = strVector.size() - scrollbarStepNumber;
		if (max >= NUM_OF_DISPLAYED_ROWS)
		{
			chatText.clear();
			size_t min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (strVector[min]->joinedTheServer == true && strVector[min]->leftTheServer == false)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer == true && strVector[min]->joinedTheServer == false)
				{
					chatText << sf::Color::Red << strVector[min]->msg << '\n';
				}
				else
				{
					if (strVector[min]->countOfLines == 1)
					{
						chatText << sf::Color::Cyan << strVector[min]->prefix << sf::Color::White << strVector[min]->msg << '\n';
					}
					else
					{
						chatText << sf::Color::White << strVector[min]->msg << '\n';
					}
				}
			}
		}
	}
	scrollbarDir = L"";
}
void Chat::scrollDown(GameVariable* gv) // function to scroll down the chat.
{
	scrollbarYPos += outerScrollBar.getSize().y / scrollbarDivisor;
	if (scrollbarStepNumber > 0)
	{
		if (strVector.size() > NUM_OF_DISPLAYED_ROWS) { scrollbarStepNumber--; }
		size_t max = strVector.size() - scrollbarStepNumber;
		if (max >= NUM_OF_DISPLAYED_ROWS)
		{
			chatText.clear();
			size_t min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; min++)
			{
				if (strVector[min]->joinedTheServer == true && strVector[min]->leftTheServer == false)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer == true && strVector[min]->joinedTheServer == false)
				{
					chatText << sf::Color::Red << strVector[min]->msg << '\n';
				}
				else
				{
					if (strVector[min]->countOfLines == 1)
					{
						chatText << sf::Color::Cyan << strVector[min]->prefix << sf::Color::White << strVector[min]->msg << '\n';
					}
					else
					{
						chatText << sf::Color::White << strVector[min]->msg << '\n';
					}
				}
			}
		}
	}
	scrollbarDir = L"";
}
bool Chat::trimString(std::wstring& str, GameVariable* gv) // string trim function.
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
		gv->setNumOfLinesInUserTextBox(1);
	}
	else if (str.size() > SINGLE_LINE_WIDTH && str.size() <= TWO_LINE_WIDTH)
	{
		gv->setNumOfLinesInUserTextBox(2);
	}
	else if (str.size() > TWO_LINE_WIDTH && str.size() <= THREE_LINE_WIDTH)
	{
		gv->setNumOfLinesInUserTextBox(3);
	}
	else if (str.size() > THREE_LINE_WIDTH && str.size() < FOUR_LINE_WIDTH)
	{
		gv->setNumOfLinesInUserTextBox(4);
	}
	return true;
}

void chatUpdate(GameVariable* gv, Chat& chat)
{
	if (gv->getLeftFromServer() == true)
	{
		chat.addString(gv);
		gv->setLeftFromServer(false);
	}

	if (gv->getJoinToServer() == true)
	{
		gv->setChatStr(gv->getJoinedMsg());
		chat.addString(gv);
		gv->setJoinToServer(false);
	}

	if (gv->getRecvMsg() == true)
	{
		gv->setChatPrefix(gv->getSenderNickname() + L": ");
		chat.addString(gv);
		if (gv->getNickname() == gv->getSenderNickname())
		{
			gv->setNumOfLinesInUserTextBox(1);
			chat.getUserText().clear();
			gv->setUserStr(L"");
		}
		gv->setSendMsg(false);
		gv->setRecvMsg(false);
	}
	chat.chatPosUpdate(getClientPos());
}
void updateScrollbarDir(GameVariable* gv, Chat& chat)
{
	if (chat.getScrollbarDir() == L"up" && ((chat.getInnerScrollBar().getPosition().y - (chat.getInnerScrollBar().getSize().y / 2.f))) > chat.getOuterScrollBar().getPosition().y - (chat.getOuterScrollBar().getSize().y / 2.f))
	{
		chat.scrollUp(gv);
	}
	else if (chat.getScrollbarDir() == L"down" && ((chat.getInnerScrollBar().getPosition().y + (chat.getInnerScrollBar().getSize().y / 2.f))) < chat.getOuterScrollBar().getPosition().y + (chat.getOuterScrollBar().getSize().y / 2.f))
	{
		chat.scrollDown(gv);
	}
}
void updateUserTextBox(GameVariable* gv, Chat& chat)
{
	if (chat.getUserTextBox().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y)) { gv->setMenuNum(1); }

	if (chat.getUserTextBox().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) || chat.getChatTextBox().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) || chat.getOuterScrollBar().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) || chat.getInnerScrollBar().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y))
	{
		gv->setChatContainsMouse(true);
	}
	else { gv->setChatContainsMouse(false); }
}