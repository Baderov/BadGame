#include "pch.h"
#include "Chat.h" // header file for working with chat.

const int SINGLE_LINE_WIDTH = 54;
const int TWO_LINE_WIDTH = 109;
const int THREE_LINE_WIDTH = 164;
const int FOUR_LINE_WIDTH = 202;
const int NUM_OF_DISPLAYED_ROWS = 10;

void Chat::init()
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

	setSenderNickname(L"");
	setUserStr(L"");
	setChatStr(L"");
	setChatPrefix(L"");
	setLeftNick(L"");
	setJoinedNick(L"");
	setJoinedMsg(L"");
	setLeftMsg(L"");
	setNumOfLinesInChat(1);
	setNumOfLinesInUserTextBox(1);
	setTextInputMode(false);
	setChatContainsMouse(false);
	setRecvMsg(false);
	setSendMsg(false);
	setLeftFromServer(false);
	setJoinToServer(true);
	setShowChat(true);
	getChatText().clear();
	getUserText().clear();
	getStrVector().clear();
}

Chat::Chat() { init(); }

void Chat::draw(std::unique_ptr<GameVariable>& gv)
{
	if (getShowChat())
	{
		gv->window.draw(getOuterScrollBar());
		gv->window.draw(getInnerScrollBar());
		gv->window.draw(getChatTextBox());
		gv->window.draw(getUserTextBox());
		gv->window.draw(getUserText());
		gv->window.draw(getChatText());
	}
}

void Chat::update(std::unique_ptr<GameVariable>& gv)
{
	updateUserTextBox(gv);
	updateScrollbarDir();

	if (getLeftFromServer())
	{
		addString();
		setLeftFromServer(false);
	}

	if (getJoinToServer())
	{
		setChatStr(getJoinedMsg());
		addString();
		setJoinToServer(false);
	}

	if (getRecvMsg())
	{
		setChatPrefix(getSenderNickname() + L": ");
		addString();
		if (gv->getNickname() == getSenderNickname())
		{
			setNumOfLinesInUserTextBox(1);
			getUserText().clear();
			setUserStr(L"");
		}
		setSendMsg(false);
		setRecvMsg(false);
	}
	chatPosUpdate(gv->getGameViewCenter());
}

void Chat::updateUserTextBox(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getServerIsNotAvailable()) { return; }

	if (getUserTextBox().getGlobalBounds().contains(gv->getMousePos())) { gv->setMenuNum(1); }
	else if (getChatTextBox().getGlobalBounds().contains(gv->getMousePos()) || getOuterScrollBar().getGlobalBounds().contains(gv->getMousePos()) || getInnerScrollBar().getGlobalBounds().contains(gv->getMousePos())) { gv->setMenuNum(2); }
	else { gv->setMenuNum(0); }
}

void Chat::updateScrollbarDir()
{
	if (getScrollbarDir() == L"up" && ((getInnerScrollBar().getPosition().y - (getInnerScrollBar().getSize().y / 2.f))) >
		getOuterScrollBar().getPosition().y - (getOuterScrollBar().getSize().y / 2.f))
	{
		scrollUp();
	}
	else if (getScrollbarDir() == L"down" && ((getInnerScrollBar().getPosition().y + (getInnerScrollBar().getSize().y / 2.f))) <
		getOuterScrollBar().getPosition().y + (getOuterScrollBar().getSize().y / 2.f))
	{
		scrollDown();
	}
}

void Chat::addString() // function to add a string to a vector.
{
	std::wstring tempStr = L"";
	size_t subStrStep = SINGLE_LINE_WIDTH - getChatPrefix().size(), max = 0, min = 0;
	if (getChatStr() != L"" && getChatStr().size() <= FOUR_LINE_WIDTH)
	{
		scrollbarYPos = 0;
		scrollbarStepNumber = 0;

		tempStr = getChatStr();
		tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), '\n'), tempStr.end());
		setChatStr(tempStr);
		tempStr = L"";

		if (getJoinToServer() && !getLeftFromServer())
		{
			strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), getJoinedMsg(), 1, true, false));
		}
		else if (getLeftFromServer() && !getJoinToServer())
		{
			strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), getLeftMsg(), 1, false, true));
		}
		else
		{
			for (size_t i = 0; i < getNumOfLinesInChat(); ++i)
			{
				if (i == 0)
				{
					tempStr = getChatStr().substr(0, subStrStep);
					strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 1, false, false));
					if (getNumOfLinesInChat() == 1 && getChatStr().size() > subStrStep)
					{
						tempStr = getChatStr().substr(subStrStep, getChatStr().size() - subStrStep);
						strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 2, false, false));
					}
				}
				else if (i == 1)
				{
					tempStr = getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 2, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (getNumOfLinesInChat() == 2 && getChatStr().size() > subStrStep)
					{
						tempStr = getChatStr().substr(subStrStep, getChatStr().size() - subStrStep);
						strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 3, false, false));
					}

				}
				else if (i == 2)
				{
					tempStr = getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 3, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (getNumOfLinesInChat() == 3 && getChatStr().size() > subStrStep)
					{
						tempStr = getChatStr().substr(subStrStep, getChatStr().size() - subStrStep);
						strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 4, false, false));
					}

				}
				else if (i == 3)
				{
					tempStr = getChatStr().substr(subStrStep, SINGLE_LINE_WIDTH);
					strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 4, false, false));
					subStrStep += SINGLE_LINE_WIDTH;
					if (getNumOfLinesInChat() == 4 && getChatStr().size() > subStrStep)
					{
						tempStr = getChatStr().substr(subStrStep, getChatStr().size() - subStrStep);
						strVector.emplace_back(std::make_unique<Chat::chatStrings>(getChatPrefix(), tempStr, 5, false, false));
					}
				}
			}
		}

		chatText.clear();
		max = strVector.size() - scrollbarStepNumber;
		if (max > NUM_OF_DISPLAYED_ROWS)
		{
			min = max - NUM_OF_DISPLAYED_ROWS;
			for (; min < max; ++min)
			{
				if (strVector[min]->joinedTheServer && !strVector[min]->leftTheServer)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer && !strVector[min]->joinedTheServer)
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
				for (; min < max; ++min)
				{
					if (strVector[min]->joinedTheServer && !strVector[min]->leftTheServer)
					{
						chatText << sf::Color::Green << strVector[min]->msg << '\n';
					}
					else if (strVector[min]->leftTheServer && !strVector[min]->joinedTheServer)
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
			for (size_t a = 0; a < strVector.size(); ++a)
			{
				if (strVector[a]->joinedTheServer && !strVector[a]->leftTheServer)
				{
					chatText << sf::Color::Green << strVector[a]->msg << '\n';
				}
				else if (strVector[a]->leftTheServer && !strVector[a]->joinedTheServer)
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
}
void Chat::chatPosUpdate(sf::Vector2f currentClientPos)
{
	chatTextBox.setPosition(std::move(currentClientPos.x) - 750.f, std::move(currentClientPos.y) + (chatTextBox.getSize().y / 2.f));
	userTextBox.setPosition(chatTextBox.getPosition().x, (chatTextBox.getPosition().y + chatTextBox.getSize().y) + 2.f);
	chatText.setPosition(chatTextBox.getPosition().x + 10.f, chatTextBox.getPosition().y + 7.f);
	userText.setPosition(userTextBox.getPosition().x + 10.f, userTextBox.getPosition().y + 7.f);
	outerScrollBar.setPosition((chatTextBox.getPosition().x + chatTextBox.getSize().x + (outerScrollBar.getSize().x / 2.f)) + 2.f, (chatTextBox.getPosition().y + (outerScrollBar.getSize().y / 2.f)));
	innerScrollBar.setPosition(outerScrollBar.getPosition().x, std::round(((outerScrollBar.getPosition().y + outerScrollBar.getSize().y / 2.f) - (innerScrollBar.getSize().y / 2.f)) + scrollbarYPos));
}
void Chat::addEndLine() // function to add the end of the line.
{
	if (getUserStr().size() == SINGLE_LINE_WIDTH || getUserStr().size() == TWO_LINE_WIDTH || getUserStr().size() == THREE_LINE_WIDTH)
	{
		setUserStr(getUserStr() + L"\n");
		userText.clear();
		userText << sf::Color::Black << getUserStr();
		setNumOfLinesInUserTextBox(getNumOfLinesInUserTextBox() + 1);
	}
}
void Chat::scrollUp() // function to scroll up the chat.
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
			for (; min < max; ++min)
			{
				if (strVector[min]->joinedTheServer && !strVector[min]->leftTheServer)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer && !strVector[min]->joinedTheServer)
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
void Chat::scrollDown() // function to scroll down the chat.
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
			for (; min < max; ++min)
			{
				if (strVector[min]->joinedTheServer && !strVector[min]->leftTheServer)
				{
					chatText << sf::Color::Green << strVector[min]->msg << '\n';
				}
				else if (strVector[min]->leftTheServer && !strVector[min]->joinedTheServer)
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
bool Chat::trimString(std::wstring& str) // string trim function.
{
	// checking for a string of spaces.
	for (size_t i = 0; i < str.size();)
	{
		if (str[i] == ' ' || str[i] == '\n') { ++i; }
		else { break; }
		if (i == str.size()) { return false; }
	}
	// checking for spaces at the beginning of the string.
	size_t subStrPos = 0;
	while (str[subStrPos] == ' ' || str[subStrPos] == '\n') { subStrPos++; }
	str = str.substr(subStrPos, str.size() - subStrPos);
	// checking for spaces at the end of the string.
	for (size_t i = str.size() - 1; i > 0; --i)
	{
		if (str[i] == ' ' || str[i] == '\n') { str.resize(str.size() - 1); }
		else { break; }
	}
	if (str.size() > 0 && str.size() <= SINGLE_LINE_WIDTH)
	{
		setNumOfLinesInUserTextBox(1);
	}
	else if (str.size() > SINGLE_LINE_WIDTH && str.size() <= TWO_LINE_WIDTH)
	{
		setNumOfLinesInUserTextBox(2);
	}
	else if (str.size() > TWO_LINE_WIDTH && str.size() <= THREE_LINE_WIDTH)
	{
		setNumOfLinesInUserTextBox(3);
	}
	else if (str.size() > THREE_LINE_WIDTH && str.size() < FOUR_LINE_WIDTH)
	{
		setNumOfLinesInUserTextBox(4);
	}
	return true;
}

std::wstring& Chat::getSenderNickname()
{
	std::lock_guard<std::mutex> lock(mtx);
	return senderNickname;
}
std::wstring& Chat::getUserStr()
{
	std::lock_guard<std::mutex> lock(mtx);
	return userStr;
}
std::wstring& Chat::getChatStr()
{
	std::lock_guard<std::mutex> lock(mtx);
	return chatStr;
}
std::wstring& Chat::getChatPrefix()
{
	std::lock_guard<std::mutex> lock(mtx);
	return chatPrefix;
}
std::wstring& Chat::getLeftNick()
{
	std::lock_guard<std::mutex> lock(mtx);
	return leftNick;
}
std::wstring& Chat::getJoinedNick()
{
	std::lock_guard<std::mutex> lock(mtx);
	return joinedNick;
}
std::wstring& Chat::getLeftMsg()
{
	std::lock_guard<std::mutex> lock(mtx);
	return leftMsg;
}
std::wstring& Chat::getJoinedMsg()
{
	std::lock_guard<std::mutex> lock(mtx);
	return joinedMsg;
}
sf::RectangleShape& Chat::getOuterScrollBar()
{
	std::lock_guard<std::mutex> lock(mtx);
	return outerScrollBar;
}
sf::RectangleShape& Chat::getInnerScrollBar()
{
	std::lock_guard<std::mutex> lock(mtx);
	return innerScrollBar;
}
sf::RectangleShape& Chat::getChatTextBox()
{
	std::lock_guard<std::mutex> lock(mtx);
	return chatTextBox;
}
sf::RectangleShape& Chat::getUserTextBox()
{
	std::lock_guard<std::mutex> lock(mtx);
	return userTextBox;
}
std::vector<std::unique_ptr<Chat::chatStrings>>& Chat::getStrVector()
{
	std::lock_guard<std::mutex> lock(mtx);
	return strVector;
}
sf::Font& Chat::getFont()
{
	std::lock_guard<std::mutex> lock(mtx);
	return font;
}
sfe::RichText& Chat::getChatText()
{
	std::lock_guard<std::mutex> lock(mtx);
	return chatText;
}
sfe::RichText& Chat::getUserText()
{
	std::lock_guard<std::mutex> lock(mtx);
	return userText;
}
float& Chat::getScrollbarDivisor()
{
	std::lock_guard<std::mutex> lock(mtx);
	return scrollbarDivisor;
}
std::wstring& Chat::getScrollbarDir()
{
	std::lock_guard<std::mutex> lock(mtx);
	return scrollbarDir;
}
bool& Chat::getShowChat()
{
	std::lock_guard<std::mutex> lock(mtx);
	return showChat;
}
bool& Chat::getChatContainsMouse()
{
	std::lock_guard<std::mutex> lock(mtx);
	return chatContainsMouse;
}
bool& Chat::getTextInputMode()
{
	std::lock_guard<std::mutex> lock(mtx);
	return textInputMode;
}
bool& Chat::getRecvMsg()
{
	std::lock_guard<std::mutex> lock(mtx);
	return recvMsg;
}
bool& Chat::getSendMsg()
{
	std::lock_guard<std::mutex> lock(mtx);
	return sendMsg;
}
bool& Chat::getLeftFromServer()
{
	std::lock_guard<std::mutex> lock(mtx);
	return leftFromServer;
}
bool& Chat::getJoinToServer()
{
	std::lock_guard<std::mutex> lock(mtx);
	return joinToServer;
}
size_t& Chat::getScrollbarStepNumber()
{
	std::lock_guard<std::mutex> lock(mtx);
	return scrollbarStepNumber;
}
int& Chat::getNumOfLinesInChat()
{
	std::lock_guard<std::mutex> lock(mtx);
	return numOfLinesInChat;
}
int& Chat::getNumOfLinesInUserTextBox()
{
	std::lock_guard<std::mutex> lock(mtx);
	return numOfLinesInUserTextBox;
}

void Chat::setNumOfLinesInChat(int tempNumOfLinesInChat)
{
	std::lock_guard<std::mutex> lock(mtx);
	numOfLinesInChat = std::move(tempNumOfLinesInChat);
}
void Chat::setNumOfLinesInUserTextBox(int tempNumOfLinesInUserTextBox)
{
	std::lock_guard<std::mutex> lock(mtx);
	numOfLinesInUserTextBox = std::move(tempNumOfLinesInUserTextBox);
}
void Chat::setOuterScrollBarPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	outerScrollBar.setPosition(std::move(posX), std::move(posY));
}
void Chat::setInnerScrollBarPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	innerScrollBar.setPosition(std::move(posX), std::move(posY));
}
void Chat::setChatTextBoxPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	chatTextBox.setPosition(std::move(posX), std::move(posY));
}
void Chat::setUserTextBoxPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	userTextBox.setPosition(std::move(posX), std::move(posY));
}
void Chat::setChatTextPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	chatText.setPosition(std::move(posX), std::move(posY));
}
void Chat::setUserTextPos(float posX, float posY)
{
	std::lock_guard<std::mutex> lock(mtx);
	userText.setPosition(std::move(posX), std::move(posY));
}
void Chat::setScrollbarDivisor(float tempDivisor)
{
	std::lock_guard<std::mutex> lock(mtx);
	scrollbarDivisor = std::move(tempDivisor);
}
void Chat::setScrollbarStepNumber(size_t tempStepNumber)
{
	std::lock_guard<std::mutex> lock(mtx);
	scrollbarStepNumber = std::move(tempStepNumber);
}
void Chat::setScrollbarDir(std::wstring tempDir)
{
	std::lock_guard<std::mutex> lock(mtx);
	scrollbarDir = std::move(tempDir);
}
void Chat::setSenderNickname(std::wstring tempSenderNickname)
{
	std::lock_guard<std::mutex> lock(mtx);
	senderNickname = std::move(tempSenderNickname);
}
void Chat::setUserStr(std::wstring tempUserStr)
{
	std::lock_guard<std::mutex> lock(mtx);
	userStr = std::move(tempUserStr);
}
void Chat::setChatStr(std::wstring tempChatStr)
{
	std::lock_guard<std::mutex> lock(mtx);
	chatStr = std::move(tempChatStr);
}
void Chat::setChatPrefix(std::wstring tempChatPrefix)
{
	std::lock_guard<std::mutex> lock(mtx);
	chatPrefix = std::move(tempChatPrefix);
}
void Chat::setLeftNick(std::wstring tempLeftNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	leftNick = std::move(tempLeftNick);
}
void Chat::setJoinedNick(std::wstring tempJoinedNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	joinedNick = std::move(tempJoinedNick);
}
void Chat::setLeftMsg(std::wstring tempLefMsg)
{
	std::lock_guard<std::mutex> lock(mtx);
	leftMsg = std::move(tempLefMsg);
}
void Chat::setJoinedMsg(std::wstring tempJoinedMsg)
{
	std::lock_guard<std::mutex> lock(mtx);
	joinedMsg = std::move(tempJoinedMsg);
}
void Chat::setShowChat(bool tempShowChat)
{
	std::lock_guard<std::mutex> lock(mtx);
	showChat = std::move(tempShowChat);
}
void Chat::setChatContainsMouse(bool tempChatContainsMouse)
{
	std::lock_guard<std::mutex> lock(mtx);
	chatContainsMouse = std::move(tempChatContainsMouse);
}
void Chat::setTextInputMode(bool tempTextInputMode)
{
	std::lock_guard<std::mutex> lock(mtx);
	textInputMode = std::move(tempTextInputMode);
}
void Chat::setRecvMsg(bool tempRecvMsg)
{
	std::lock_guard<std::mutex> lock(mtx);
	recvMsg = std::move(tempRecvMsg);
}
void Chat::setSendMsg(bool tempSendMsg)
{
	std::lock_guard<std::mutex> lock(mtx);
	sendMsg = std::move(tempSendMsg);
}
void Chat::setLeftFromServer(bool tempLeftFromServer)
{
	std::lock_guard<std::mutex> lock(mtx);
	leftFromServer = std::move(tempLeftFromServer);
}
void Chat::setJoinToServer(bool tempJoinToServer)
{
	std::lock_guard<std::mutex> lock(mtx);
	joinToServer = std::move(tempJoinToServer);
}