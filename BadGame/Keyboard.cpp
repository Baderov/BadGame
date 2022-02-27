#include "Keyboard.h"

void authKeyboard(GameVariables* gv, sf::Event& event, sf::Text& nicknameText, bool& input) // функция обновления клавиш во время авторизации.
{
	if (event.type == sf::Event::TextEntered && input == true)
	{
		if (event.text.unicode == 8 && gv->playerName.size() > 0)
		{
			gv->playerName.resize(gv->playerName.size() - 1);
			nicknameText.setString("");
			nicknameText.setString(nicknameText.getString() + "\n" + gv->playerName);
		}
		else if (gv->playerName.size() < 15 && ((event.text.unicode > 47 && event.text.unicode < 58) || (event.text.unicode > 64 && event.text.unicode < 91) || (event.text.unicode > 96 && event.text.unicode < 123)))
		{
			gv->playerName += event.text.unicode;
			nicknameText.setString("");
			nicknameText.setString(nicknameText.getString() + "\n" + gv->playerName);
		}		
	}
}