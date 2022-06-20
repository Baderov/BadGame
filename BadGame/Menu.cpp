#include "Menu.h"

void graphicsSettingsMenu(GameVariables* gv)
{
	graphicsSettingsMenuUpdate(gv);
	//std::cout << gv->lineNumberInConsole++ << ": I'm in the graphics settings menu!" << std::endl;
	while (gv->window.isOpen()) // пока меню открыто.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0; // присваиваем номер меню.

		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}

		for (auto& el : gv->buttonsVec)
		{
			if (((gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080) || (sf::VideoMode::getFullscreenModes()[0].width < 1920 && sf::VideoMode::getFullscreenModes()[0].height < 1080)) && el->getName() == "fullHDResolutionButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
			else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768 && el->getName() == "HDResolutionButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}

			if (gv->isFullscreen == true && el->getName() == "fullscreenModeButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
			else if (gv->isFullscreen == false && el->getName() == "windowedModeButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}

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
				if (el->getSprite().getFillColor() != gv->greyColor)
				{
					el->getSprite().setFillColor(sf::Color::Yellow);

					if (el->getName() == "HDResolutionButton")
					{
						gv->menuNum = 6;
					}
					if (el->getName() == "fullHDResolutionButton")
					{
						gv->menuNum = 7;
					}
					if (el->getName() == "windowedModeButton")
					{
						gv->menuNum = 8;
					}
					if (el->getName() == "fullscreenModeButton")
					{
						gv->menuNum = 9;
					}
					if (el->getName() == "engLangButton")
					{
						gv->menuNum = 10;
					}
					if (el->getName() == "rusLangButton")
					{
						gv->menuNum = 11;
					}
					if (el->getName() == "backButton")
					{
						gv->menuNum = 12;
					}
				}
			}
		}


		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->menuNum = 14;
				gv->buttonsVec.clear();
				gv->labelsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); gv->labelsVec.clear(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { gv->buttonsVec.clear(); gv->labelsVec.clear(); return; } // если нажали левую кнопку мыши.	
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

void settingsMenu(GameVariables* gv)
{
	settingsMenuUpdate(gv);
	//std::cout << gv->lineNumberInConsole++ << ": I'm in the settings menu!" << std::endl;
	while (gv->window.isOpen()) // пока меню открыто.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0; // присваиваем номер меню.

		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
			{
				el->getSprite().setFillColor(sf::Color::Yellow);
				if (el->getName() == "graphicsSettingsButton")
				{
					gv->menuNum = 4;
				}
				if (el->getName() == "backButton")
				{
					gv->menuNum = 5;
				}
			}
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->menuNum = 13;
				gv->buttonsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { gv->buttonsVec.clear(); return; } // если нажали левую кнопку мыши.	
		}
		gv->window.clear(sf::Color::Black); // очищаем окно черным цветом.
		for (auto& el : gv->buttonsVec)
		{
			gv->window.draw(el->getSprite());
			gv->window.draw(el->getText());
		}
		gv->window.display(); // отображаем в окне.
	}
}

void mainMenu(GameVariables* gv, Entity*& player)
{
	mainMenuUpdate(gv, player);
	//std::cout << gv->lineNumberInConsole++ << ": I'm in the main menu!" << std::endl;
	while (gv->window.isOpen()) // пока меню открыто.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0; // присваиваем номер меню.

		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White);
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y) && el->getSprite().getFillColor() != gv->greyColor)
			{
				el->getSprite().setFillColor(sf::Color::Yellow);
				if (el->getName() == "singlePlayerButton")
				{
					gv->menuNum = 1;
				}
				if (el->getName() == "settingsButton")
				{
					gv->menuNum = 2;
				}
				if (el->getName() == "exitButton")
				{
					gv->menuNum = 3;
				}
				if (el->getName() == "backToMenuButton")
				{
					gv->menuNum = 15;
				}
				if (el->getName() == "continueButton")
				{
					gv->menuNum = 16;
				}
				if (el->getName() == "restartGameButton")
				{
					gv->menuNum = 1;
				}
				if (el->getName() == "multiPlayerButton")
				{
					gv->menuNum = 17;
				}
			}
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape && gv->isGameStarted == true) // если отпустили кнопку Escape.
			{
				gv->menuNum = 16;
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { gv->buttonsVec.clear(); return; } // если нажали левую кнопку мыши.	
		}
		gv->window.clear(sf::Color::Black); // очищаем окно черным цветом.
		for (auto& el : gv->buttonsVec)
		{
			gv->window.draw(el->getSprite());
			gv->window.draw(el->getText());
		}

		gv->window.display(); // отображаем в окне.
	}
}

void multiplayerMenu(GameVariables* gv)
{
	multiplayerMenuUpdate(gv);
	while (gv->window.isOpen()) // пока меню открыто.
	{
		gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // получаем коорды мыши.
		gv->menuNum = 0; // присваиваем номер меню.

		for (auto& el : gv->buttonsVec)
		{
			el->getSprite().setFillColor(sf::Color::White); // заливаем объект цветом.
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
			{
				el->getSprite().setFillColor(sf::Color::Yellow);

				if (el->getName() == "connectButton")
				{
					gv->menuNum = 0;
				}
				if (el->getName() == "cancelButton")
				{
					gv->menuNum = 0;
				}
			}
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->menuNum = 13;
				gv->buttonsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { gv->buttonsVec.clear(); return; } // если нажали левую кнопку мыши.	
		}
		gv->window.clear(sf::Color::Black); // очищаем окно черным цветом.
		for (auto& el : gv->buttonsVec)
		{
			gv->window.draw(el->getSprite());
			gv->window.draw(el->getText());
		}
		gv->window.display(); // отображаем в окне.
	}
}

void menuEventHandler(GameVariables* gv, Entity*& player)
{
	mainMenu(gv, player);
	while (gv->window.isOpen()) // пока меню открыто.
	{
		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); }
		}

		switch (gv->menuNum)
		{
		case 1:
			gv->menuNum = 0;
			gv->isGameStarted = false;
			return;
			break;
		case 2:
			gv->menuNum = 0;
			settingsMenu(gv);
			break;
		case 3:
			gv->menuNum = 0;
			gv->window.close();
			return;
			break;
		case 4:
			gv->menuNum = 0;
			graphicsSettingsMenu(gv);
			break;
		case 5:
			gv->menuNum = 0;
			mainMenu(gv, player);
			break;
		case 6:
			gv->menuNum = 0;
			if (gv->isFullscreen == true) { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Fullscreen); }
			else { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Close); }
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
			graphicsSettingsMenu(gv);
			break;
		case 7:
			gv->menuNum = 0;
			if (gv->isFullscreen == true) { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Fullscreen); }
			else { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Close); }
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
			graphicsSettingsMenu(gv);
			break;
		case 8:
			gv->menuNum = 0;
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Close);
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
			gv->isFullscreen = false;
			graphicsSettingsMenu(gv);
			break;
		case 9:
			gv->menuNum = 0;
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Fullscreen);
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
			gv->isFullscreen = true;
			graphicsSettingsMenu(gv);
			break;
		case 10:
			gv->menuNum = 0;
			gv->gameLanguage = 'e';
			graphicsSettingsMenu(gv);
			break;
		case 11:
			gv->menuNum = 0;
			gv->gameLanguage = 'r';
			graphicsSettingsMenu(gv);
			break;
		case 12:
			gv->menuNum = 0;
			settingsMenu(gv);
			break;
		case 13:
			gv->menuNum = 0;
			mainMenu(gv, player);
			break;
		case 14:
			gv->menuNum = 0;
			settingsMenu(gv);
			break;
		case 15:
			gv->menuNum = 0;
			gv->isGameStarted = false;
			mainMenu(gv, player);
			break;
		case 16:
			gv->menuNum = 0;
			gv->isGameStarted = true;
			return;
			break;
		case 17:
			gv->menuNum = 0;

			break;






































		}
	}
}