#include "Keyboard.h" // header file for handling keyboard events.

const int BACKSPACE_CODE = 8;
const int SPACE_CODE = 32;
const int QUESTION_MARK_CODE = 63;
const int DOUBLE_QUOTES_CODE = 34;
const int SINGLE_QUOTES_CODE = 39;
const int BACKSLASH_CODE = 92;

void keyboardEventHandler(GameVariables* gv) // keyboard event handling function.
{
	if (gv->input == 'n')
	{
		if (gv->event.type == sf::Event::TextEntered)
		{
			if (gv->event.text.unicode == BACKSPACE_CODE)
			{
				if (gv->nickname.size() > 0)
				{
					gv->nickname.resize(gv->nickname.size() - 1);
				}
			}
			else if (gv->event.text.unicode == QUESTION_MARK_CODE)
			{
				gv->nickname += L"\?";
			}
			else if (gv->event.text.unicode == DOUBLE_QUOTES_CODE)
			{
				gv->nickname += L"\"";
			}
			else if (gv->event.text.unicode == SINGLE_QUOTES_CODE)
			{
				gv->nickname += L"\'";
			}
			else if (gv->event.text.unicode == BACKSLASH_CODE)
			{
				gv->nickname += L"\\";
			}
			else 
			{
				if (gv->nickname.size() < 15 && gv->event.text.unicode != SPACE_CODE)
				{
					gv->nickname += gv->event.text.unicode;
				}
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
	else
	{
		if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Backspace)
		{
			if (gv->input == 'i' && gv->serverIP.size() > 0)
			{
				gv->serverIP.resize(gv->serverIP.size() - 1);
			}
			else if (gv->input == 'p' && gv->tempPort.size() > 0)
			{
				gv->tempPort.resize(gv->tempPort.size() - 1);
				gv->serverPort = atoi(gv->tempPort.c_str());
			}
		}

		else if (gv->event.type == sf::Event::KeyPressed)
		{
			switch (gv->event.key.code)
			{
			case sf::Keyboard::Num0:
				gv->symbol = '0';
				break;
			case sf::Keyboard::Num1:
				gv->symbol = '1';
				break;
			case sf::Keyboard::Num2:
				gv->symbol = '2';
				break;
			case sf::Keyboard::Num3:
				gv->symbol = '3';
				break;
			case sf::Keyboard::Num4:
				gv->symbol = '4';
				break;
			case sf::Keyboard::Num5:
				gv->symbol = '5';
				break;
			case sf::Keyboard::Num6:
				gv->symbol = '6';
				break;
			case sf::Keyboard::Num7:
				gv->symbol = '7';
				break;
			case sf::Keyboard::Num8:
				gv->symbol = '8';
				break;
			case sf::Keyboard::Num9:
				gv->symbol = '9';
				break;
			case sf::Keyboard::Period:
				gv->symbol = '.';
				break;
			default:
				gv->symbol = ' ';
				break;
			}

			if (gv->input == 'i' && gv->serverIP.size() < 15 && gv->symbol != ' ')
			{
				gv->serverIP += gv->symbol;
			}
			else if (gv->input == 'p' && gv->tempPort.size() < 15 && gv->symbol != ' ')
			{
				gv->tempPort += gv->symbol;
				gv->serverPort = atoi(gv->tempPort.c_str());			
			}
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getName() == "ipFieldButton")
			{
				el->getText().setString(gv->serverIP);
				el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
			}
			else if (el->getName() == "portFieldButton")
			{
				el->getText().setString(gv->tempPort);
				el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
			}
		}
	}
}