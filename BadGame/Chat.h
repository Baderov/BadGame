#ifndef CHAT_H
#define CHAT_H

#include "RichText.hpp"
#include "Variables.h"

class Chat // declare a class for creating a chat.
{
public:
	struct chatStrings // chatStrings structure.
	{
		chatStrings(std::wstring prefix, std::wstring msg, int countOfLines, bool joinedTheServer, bool leftTheServer) // chatStrings constructor.
		{
			this->prefix = prefix;
			this->msg = msg;
			this->countOfLines = countOfLines;
			this->joinedTheServer = joinedTheServer;
			this->leftTheServer = leftTheServer;
		}
		std::wstring prefix = L"";
		std::wstring msg = L"";
		int countOfLines = 1;
		bool joinedTheServer = false;
		bool leftTheServer = false;
	};

	Chat(); // chat constructor.

	void init();
	void update(std::unique_ptr<GameVariable>& gv);
	void draw(std::unique_ptr<GameVariable>& gv);

	void updateUserTextBox(std::unique_ptr<GameVariable>& gv);
	void updateScrollbarDir();
	void chatPosUpdate(sf::Vector2f currentClientPos);
	void addString(); // function to add a string to a vector.
	void addEndLine(); // function to add the end of the line.
	void scrollUp(); // function to scroll up the chat.
	void scrollDown(); // function to scroll down the chat.
	bool trimString(std::wstring& str); // string trim function.

	sf::RectangleShape& getOuterScrollBar(); // function to get outer scrollbar.
	sf::RectangleShape& getInnerScrollBar(); // function to get inner scrollbar.
	sf::RectangleShape& getChatTextBox(); // function to get chat textbox.
	sf::RectangleShape& getUserTextBox(); // function to get user textbox.
	std::vector<std::unique_ptr<chatStrings>>& getStrVector(); // function to get string vector.
	sf::Font& getFont(); // function to get font.
	sfe::RichText& getChatText(); // function to get chat text.
	sfe::RichText& getUserText(); // function to get user text.
	std::wstring& getScrollbarDir();
	std::wstring& getSenderNickname();
	std::wstring& getUserStr();
	std::wstring& getChatStr();
	std::wstring& getChatPrefix();
	std::wstring& getLeftNick();
	std::wstring& getJoinedNick();
	std::wstring& getLeftMsg();
	std::wstring& getJoinedMsg();
	int& getNumOfLinesInChat();
	int& getNumOfLinesInUserTextBox();
	size_t& getScrollbarStepNumber();
	float& getScrollbarDivisor();
	bool& getShowChat();
	bool& getChatContainsMouse();
	bool& getTextInputMode();
	bool& getRecvMsg();
	bool& getSendMsg();
	bool& getLeftFromServer();
	bool& getJoinToServer();

	void setOuterScrollBarPos(float posX, float posY);
	void setInnerScrollBarPos(float posX, float posY);
	void setChatTextBoxPos(float posX, float posY);
	void setUserTextBoxPos(float posX, float posY);
	void setChatTextPos(float posX, float posY);
	void setUserTextPos(float posX, float posY);
	void setScrollbarDivisor(float tempDivisor);
	void setNumOfLinesInChat(int tempNumOfLinesInChat);
	void setNumOfLinesInUserTextBox(int tempNumOfLinesInUserTextBox);
	void setScrollbarStepNumber(size_t tempStepNumber);
	void setScrollbarDir(std::wstring tempDir);
	void setSenderNickname(std::wstring tempSenderNickname);
	void setUserStr(std::wstring tempUserStr);
	void setChatStr(std::wstring tempChatStr);
	void setChatPrefix(std::wstring tempChatPrefix);
	void setLeftNick(std::wstring tempLeftNick);
	void setJoinedNick(std::wstring tempJoinedNick);
	void setLeftMsg(std::wstring tempLefMsg);
	void setJoinedMsg(std::wstring tempJoinedMsg);
	void setShowChat(bool tempShowChat);
	void setChatContainsMouse(bool tempChatContainsMouse);
	void setTextInputMode(bool tempTextInputMode);
	void setRecvMsg(bool tempRecvMsg);
	void setSendMsg(bool tempSendMsg);
	void setLeftFromServer(bool tempLeftFromServer);
	void setJoinToServer(bool tempJoinToServer);

private:
	sf::RectangleShape outerScrollBar, innerScrollBar, chatTextBox, userTextBox;
	sf::Color greyColor;
	std::vector<std::unique_ptr<chatStrings>> strVector;
	sf::Font font;
	sfe::RichText chatText, userText;
	std::mutex mtx;

	std::wstring senderNickname;
	std::wstring chatStr;
	std::wstring userStr;
	std::wstring chatPrefix;
	std::wstring leftNick;
	std::wstring joinedNick;
	std::wstring joinedMsg;
	std::wstring leftMsg;
	std::wstring scrollbarDir;

	int numOfLinesInChat;
	int numOfLinesInUserTextBox;
	size_t scrollbarStepNumber;
	float scrollbarDivisor;
	float scrollbarYPos;

	bool chatContainsMouse;
	bool textInputMode;
	bool recvMsg;
	bool sendMsg;
	bool leftFromServer;
	bool joinToServer;
	bool showChat;
};

#endif