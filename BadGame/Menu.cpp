#include "Menu.h"

void graphicsSettingsMenu(GameVariables* gv)
{
	graphicsSettingsMenuUpdate(gv);
	std::cout << gv->lineNumberInConsole++ << ": I'm in the graphics settings menu!" << std::endl;
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

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { return; } // если нажали левую кнопку мыши.	
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
	std::cout << gv->lineNumberInConsole++ << ": I'm in the settings menu!" << std::endl;
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
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { return; } // если нажали левую кнопку мыши.	
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

void mainMenu(GameVariables* gv)
{
	mainMenuUpdate(gv);
	std::cout << gv->lineNumberInConsole++ << ": I'm in the main menu!" << std::endl;
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
			if (el->getSprite().getGlobalBounds().contains(gv->mousePos.x, gv->mousePos.y))
			{
				el->getSprite().setFillColor(sf::Color::Yellow);
				if (el->getName() == "startButton")
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
			}
		}

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; } // если состояние события приняло значение "Закрыто" - окно закрывается.
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->menuNum > 0) { return; } // если нажали левую кнопку мыши.	
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

void menuEventHandler(GameVariables* gv)
{
	mainMenu(gv);
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
			mainMenu(gv);
			break;
		case 6:
			gv->menuNum = 0;
			if (gv->isFullscreen == true) { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Fullscreen); }
			else { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Close); }
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			graphicsSettingsMenu(gv);
			break;
		case 7:
			gv->menuNum = 0;
			if (gv->isFullscreen == true) { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Fullscreen); }
			else { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Close); }
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			graphicsSettingsMenu(gv);
			break;
		case 8:
			gv->menuNum = 0;
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Close);
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
			gv->isFullscreen = false;
			graphicsSettingsMenu(gv);
			break;
		case 9:
			gv->menuNum = 0;
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Fullscreen);
			gv->window.setFramerateLimit(75); // ставим ограничение на фпс.
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













































		}
	}
}