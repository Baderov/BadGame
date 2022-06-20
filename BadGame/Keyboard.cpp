#include "Keyboard.h"

void authKeyboard(GameVariables* gv, sf::Event& event, bool& input) // функция обновления клавиш во время авторизации.
{
	if (gv->event.type == sf::Event::TextEntered && input == true)
	{
		if (gv->event.text.unicode == 8 && gv->nickname.size() > 0)
		{
			gv->nickname.resize(gv->nickname.size() - 1);
		}
		else if (gv->nickname.size() < 15 && ((gv->event.text.unicode > 47 && gv->event.text.unicode < 58) || (gv->event.text.unicode > 64 && gv->event.text.unicode < 91) || (gv->event.text.unicode > 96 && gv->event.text.unicode < 123)))
		{
			gv->nickname += gv->event.text.unicode;
		}
		for (auto& el : gv->buttonsVec)
		{
			if (el->getName() == "nicknameFieldButton")
			{
				el->getText().setString(gv->nickname);
				el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
				break;
			}
		}
	}
}