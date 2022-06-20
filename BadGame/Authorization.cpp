#include "Authorization.h" // подключаем заголовочный файл.

void authorization(GameVariables* gv)
{
	authorizationUpdate(gv);
	gv->nickname = "";
	bool input = false;

	while (gv->window.isOpen()) // пока открыто окно.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0;
		for (auto& el : gv->buttonsVec)
		{
			if (el->getName() == "enterButton" || el->getName() == "exitButton" || el->getName() == "engLangButton" || el->getName() == "rusLangButton")
			{
				el->getSprite().setFillColor(sf::Color::White);
			}
		}
		for (auto& el : gv->buttonsVec)
		{
			if (gv->gameLanguage == 'e' && el->getName() == "engLangButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}

			else if (gv->gameLanguage == 'r' && el->getName() == "rusLangButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
			{
				if (el->getName() == "nicknameFieldButton")
				{
					gv->menuNum = 1;
				}

				if (el->getName() == "enterButton")
				{
					gv->menuNum = 2;
					el->getSprite().setFillColor(sf::Color::Yellow);
				}

				if (el->getName() == "exitButton")
				{
					gv->menuNum = 3;
					el->getSprite().setFillColor(sf::Color::Yellow);
				}

				if (el->getSprite().getFillColor() != gv->greyColor)
				{
					if (el->getName() == "engLangButton")
					{
						gv->menuNum = 4;
						el->getSprite().setFillColor(sf::Color::Yellow);
					}
					if (el->getName() == "rusLangButton")
					{
						gv->menuNum = 5;
						el->getSprite().setFillColor(sf::Color::Yellow);
					}
				}
			}
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->menuNum = 2;
				return;
			}

			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->labelsVec.clear(); gv->buttonsVec.clear(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.

			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left) // если нажали левую кнопку мыши.
			{
				if (gv->menuNum == 0)
				{
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "nicknameFieldButton")
						{
							el->getSprite().setFillColor(sf::Color::White);
							input = false;
							break;
						}
					}
				}

				if (gv->menuNum == 1)
				{
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "nicknameFieldButton")
						{
							el->getSprite().setFillColor(sf::Color::Green);
							input = true;
							break;
						}
					}
				}

				if (gv->menuNum == 2)
				{
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "enterButton")
						{
							if (gv->nickname.length() >= 1)
							{
								el->getSprite().setFillColor(sf::Color::White);
								gv->menuNum = 0;
								gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Close); // создаём окно и устанавливаем видеорежим, заголовок окна.
								gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
								gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
								return;
							}
							break;
						}
					}
				}

				if (gv->menuNum == 3)
				{
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "exitButton")
						{
							gv->window.close();
							break;
						}
					}
				}

				if (gv->menuNum == 4)
				{
					gv->menuNum = 0;
					gv->gameLanguage = 'e';
					authorizationUpdate(gv);
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

				if (gv->menuNum == 5)
				{
					gv->menuNum = 0;
					gv->gameLanguage = 'r';
					authorizationUpdate(gv);
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

			authKeyboard(gv, gv->event, input);
		}
		gv->window.clear(sf::Color::Black); // очищаем окно черным цветом.
		for (auto& el : gv->buttonsVec)
		{
			gv->window.draw(el->getSprite());
			gv->window.draw(el->getText());
		}
		for (auto& el : gv->labelsVec)
		{
			gv->window.draw(el->getText());
		}
		gv->window.display(); // отображаем в окне.
	}
}