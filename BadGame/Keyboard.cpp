#include "Keyboard.h" // header file for handling keyboard events.

const int BACKSPACE_CODE = 8;
const int TABULATION_CODE = 9;
const int SPACE_CODE = 32;
const int QUESTION_MARK_CODE = 63;
const int DOUBLE_QUOTES_CODE = 34;
const int SINGLE_QUOTES_CODE = 39;
const int BACKSLASH_CODE = 92;

#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

void keyboardEventHandler(GameVariable* gv) // keyboard event handling function.
{
	if (gv->getInput() == 'n')
	{
		if (gv->event.type == sf::Event::TextEntered)
		{
			if (gv->event.text.unicode == BACKSPACE_CODE)
			{
				if (gv->getNickname().size() > 0)
				{
					std::wstring tempNick = gv->getNickname();
					tempNick.resize(tempNick.size() - 1);
					gv->setNickname(tempNick);
				}
			}
			else if (gv->event.text.unicode == QUESTION_MARK_CODE)
			{
				gv->setNickname(gv->getNickname() + L"\?");
			}
			else if (gv->event.text.unicode == DOUBLE_QUOTES_CODE)
			{
				gv->setNickname(gv->getNickname() + L"\"");
			}
			else if (gv->event.text.unicode == SINGLE_QUOTES_CODE)
			{
				gv->setNickname(gv->getNickname() + L"\'");
			}
			else if (gv->event.text.unicode == BACKSLASH_CODE)
			{
				gv->setNickname(gv->getNickname() + L"\\");
			}
			else
			{
				if (gv->getNickname().size() < 15 && gv->event.text.unicode != SPACE_CODE && gv->event.text.unicode != TABULATION_CODE)
				{
					std::wstring tempNick = gv->getNickname();
					tempNick += gv->event.text.unicode;
					gv->setNickname(tempNick);
				}
			}
			for (auto& el : gv->buttonsVec)
			{
				if (el->getName() == "nicknameFieldButton")
				{
					el->getText().setString(gv->getNickname());
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
			if (gv->getInput() == 'i' && gv->getServerIP().size() > 0)
			{
				std::string tempServerIP = gv->getServerIP();
				tempServerIP.resize(tempServerIP.size() - 1);
				gv->setServerIP(tempServerIP);
			}
			else if (gv->getInput() == 'p' && gv->getTempPort().size() > 0)
			{
				std::string tempPort = gv->getTempPort();
				tempPort.resize(tempPort.size() - 1);
				gv->setServerPort(atoi(tempPort.c_str()));
				gv->setTempPort(tempPort);
			}
		}

		else if (gv->event.type == sf::Event::KeyPressed)
		{
			switch (gv->event.key.code)
			{
			case sf::Keyboard::Num0:
				gv->setSymbol('0');
				break;
			case sf::Keyboard::Num1:
				gv->setSymbol('1');
				break;
			case sf::Keyboard::Num2:
				gv->setSymbol('2');
				break;
			case sf::Keyboard::Num3:
				gv->setSymbol('3');
				break;
			case sf::Keyboard::Num4:
				gv->setSymbol('4');
				break;
			case sf::Keyboard::Num5:
				gv->setSymbol('5');
				break;
			case sf::Keyboard::Num6:
				gv->setSymbol('6');
				break;
			case sf::Keyboard::Num7:
				gv->setSymbol('7');
				break;
			case sf::Keyboard::Num8:
				gv->setSymbol('8');
				break;
			case sf::Keyboard::Num9:
				gv->setSymbol('9');
				break;
			case sf::Keyboard::Period:
				if (gv->getInput() == 'i')
				{
					gv->setSymbol('.');
				}
				else if (gv->getInput() == 'p')
				{
					gv->setSymbol(' ');
				}
				break;
			default:
				gv->setSymbol(' ');
				break;
			}

			if (gv->getInput() == 'i' && gv->getServerIP().size() < 15 && gv->getSymbol() != ' ')
			{
				gv->setServerIP(gv->getServerIP() + gv->getSymbol());
			}
			else if (gv->getInput() == 'p' && gv->getTempPort().size() < 15 && gv->getSymbol() != ' ')
			{
				gv->setTempPort(gv->getTempPort() + gv->getSymbol());
				gv->setServerPort(atoi(gv->getTempPort().c_str()));
			}
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getName() == "ipFieldButton")
			{
				el->getText().setString(gv->getServerIP());
				el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
			}
			else if (el->getName() == "portFieldButton")
			{
				el->getText().setString(gv->getTempPort());
				el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
			}
		}
	}
}