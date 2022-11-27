#include "Menu.h" // header file for working with the menu.
#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::wcout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

void errorChecking(GameVariable* gv) // error checking function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;

	for (auto& el : gv->labelsVec)
	{
		if (el->getName() == "errorLabel" && gv->multiplayerError == MultiplayerErrors::NickMustContainMoreChars)
		{
			if (gv->getGameLanguage() == 'e') { el->getText().setString(L"Nickname must contain more than 2 characters!"); }
			else if (gv->getGameLanguage() == 'r') { el->getText().setString(L"Никнейм должен содержать более 2 символов!"); }

			el->getText().setOrigin(round(el->getText().getLocalBounds().left + (el->getText().getLocalBounds().width / 2.f)), round(el->getText().getLocalBounds().top + (el->getText().getLocalBounds().height / 2.f)));
			el->getText().setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f));
		}
		else if (el->getName() == "errorLabel" && gv->multiplayerError == MultiplayerErrors::ServerIsNotAvailable)
		{
			if (gv->getGameLanguage() == 'e') { el->getText().setString(L"Server is not available!"); }
			else if (gv->getGameLanguage() == 'r') { el->getText().setString(L"Сервер недоступен!"); }

			el->getText().setOrigin(round(el->getText().getLocalBounds().left + (el->getText().getLocalBounds().width / 2.f)), round(el->getText().getLocalBounds().top + (el->getText().getLocalBounds().height / 2.f)));
			el->getText().setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f));
		}
		else if (el->getName() == "errorLabel" && gv->multiplayerError == MultiplayerErrors::NicknameIsAlreadyTaken)
		{
			if (gv->getGameLanguage() == 'e') { el->getText().setString(L"Nickname is already taken!"); }
			else if (gv->getGameLanguage() == 'r') { el->getText().setString(L"Никнейм уже занят!"); }

			el->getText().setOrigin(round(el->getText().getLocalBounds().left + (el->getText().getLocalBounds().width / 2.f)), round(el->getText().getLocalBounds().top + (el->getText().getLocalBounds().height / 2.f)));
			el->getText().setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f));
		}

		else if (el->getName() == "errorLabel" && gv->multiplayerError == MultiplayerErrors::WrongIP)
		{
			if (gv->getGameLanguage() == 'e') { el->getText().setString(L"The number of dots in the IP address must be 3!"); }
			else if (gv->getGameLanguage() == 'r') { el->getText().setString(L"В IP адресе должно быть 3 точки!"); }

			el->getText().setOrigin(round(el->getText().getLocalBounds().left + (el->getText().getLocalBounds().width / 2.f)), round(el->getText().getLocalBounds().top + (el->getText().getLocalBounds().height / 2.f)));
			el->getText().setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f));
		}

		else if (el->getName() == "errorLabel" && gv->multiplayerError == MultiplayerErrors::WrongPort)
		{
			if (gv->getGameLanguage() == 'e') { el->getText().setString(L"Enter port!"); }
			else if (gv->getGameLanguage() == 'r') { el->getText().setString(L"Введите порт"); }

			el->getText().setOrigin(round(el->getText().getLocalBounds().left + (el->getText().getLocalBounds().width / 2.f)), round(el->getText().getLocalBounds().top + (el->getText().getLocalBounds().height / 2.f)));
			el->getText().setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f));
		}
	}
}

void updateFields(GameVariable* gv) // function for update fields in multiplayer menu.
{
	gv->setNickname(L"");
	gv->setServerIP("");
	gv->setTempPort("");
	gv->setServerPort(2000);

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
		else if (el->getName() == "nicknameFieldButton")
		{
			el->getText().setString(gv->getNickname());
			el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
		}
	}
}

void multiplayerMenu(GameVariable* gv) // multiplayer menu function.
{
	multiplayerMenuUpdate(gv);
	updateFields(gv);
	gv->multiplayerError = MultiplayerErrors::NoErrors;
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		gv->setMenuNum(0);

		if (gv->getNickname().size() >= 3 && gv->multiplayerError == MultiplayerErrors::NickMustContainMoreChars) { gv->multiplayerError = MultiplayerErrors::NoErrors; }

		if (gv->getMultiPlayerGame() == true && gv->getNetworkEnd() == true)
		{
			gv->setMenuNum(23);
			gv->buttonsVec.clear();
			gv->labelsVec.clear();
			return;
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getName() == "connectButton" || el->getName() == "backButton") { el->getSprite().setFillColor(sf::Color::White); }
			if (gv->getAllowButtons() == false) { el->getSprite().setFillColor(gv->greyColor); }
		}

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) && el->getSprite().getFillColor() != gv->greyColor)
			{
				if (el->getName() == "backButton") { gv->setMenuNum(5); el->getSprite().setFillColor(sf::Color::Yellow); }
				if (el->getName() == "ipFieldButton") { gv->setMenuNum(18); }
				if (el->getName() == "portFieldButton") { gv->setMenuNum(19); }
				if (el->getName() == "connectButton") { gv->setMenuNum(20); el->getSprite().setFillColor(sf::Color::Yellow); }
				if (el->getName() == "nicknameFieldButton") { gv->setMenuNum(22); }
			}
		}

		while (gv->window.pollEvent(gv->event))
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape)
			{
				gv->setMenuNum(13);
				gv->buttonsVec.clear();
				gv->labelsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); gv->labelsVec.clear(); return; }
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->getAllowButtons() == true)
			{
				switch (gv->getMenuNum())
				{
				case 0:
					gv->setInput(' ');
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "ipFieldButton" || el->getName() == "portFieldButton" || el->getName() == "nicknameFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
					}
					break;

				case 5:
					gv->buttonsVec.clear();
					gv->labelsVec.clear();
					return;

				case 18:
					gv->setInput('i');
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "ipFieldButton") { el->getSprite().setFillColor(sf::Color::Green); }
						if (el->getName() == "portFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
						if (el->getName() == "nicknameFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
					}
					break;

				case 19:
					gv->setInput('p');
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "ipFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
						if (el->getName() == "portFieldButton") { el->getSprite().setFillColor(sf::Color::Green); }
						if (el->getName() == "nicknameFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
					}
					break;

				case 22:
					gv->setInput('n');
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "ipFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
						if (el->getName() == "portFieldButton") { el->getSprite().setFillColor(sf::Color::White); }
						if (el->getName() == "nicknameFieldButton") { el->getSprite().setFillColor(sf::Color::Green); }
					}
					break;

				case 20:
					if (gv->getNetworkEnd() == true)
					{
						int countOfDotsInIP = 0;
						for (int i = 0; i < gv->getServerIP().size(); i++)
						{
							if (gv->getServerIP()[i] == '.') { countOfDotsInIP++; }
						}
						gv->multiplayerError = MultiplayerErrors::NoErrors;
						if (gv->getNickname().size() < 3) { gv->multiplayerError = MultiplayerErrors::NickMustContainMoreChars; break; }
						if (countOfDotsInIP != 3) { gv->multiplayerError = MultiplayerErrors::WrongIP; break; }
						if (gv->getTempPort().size() < 1) { gv->multiplayerError = MultiplayerErrors::WrongPort; break; }

						gv->setAllowButtons(false);
						resetVariables(gv);
						gv->setViewSize(sf::Vector2f(1920.f, 1080.f));
						gv->setMultiPlayerGame(true);
						std::thread networkThread([&]() { startNetwork(gv); });
						networkThread.detach();
					}
					break;
				}
			}
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.control && gv->event.key.code == sf::Keyboard::V)
			{
				std::string clipboardText = sf::Clipboard::getString();
				if (clipboardText.size() > 15) { clipboardText = clipboardText.substr(0, 15); }
				if (gv->getInput() == 'i')
				{
					gv->setServerIP(clipboardText);
					for (auto& el : gv->buttonsVec)
					{
						if (el->getName() == "ipFieldButton")
						{
							el->getText().setString(gv->getServerIP());
							el->getText().setPosition(el->getSprite().getGlobalBounds().left + 11.f, el->getSprite().getPosition().y - (el->getSprite().getGlobalBounds().height / 2.f) - 5.f);
						}
					}
				}
			}
			keyboardEventHandler(gv);
			errorChecking(gv);
		}
		gv->window.clear(sf::Color::Black);
		for (auto& el : gv->buttonsVec) { gv->window.draw(el->getSprite()); gv->window.draw(el->getText()); }
		for (auto& el : gv->labelsVec)
		{
			if ((el->getName() == "errorLabel" && gv->multiplayerError != MultiplayerErrors::NoErrors) || el->getName() == "enterIPLabel" || el->getName() == "enterPortLabel" || el->getName() == "enterNicknameLabel")
			{
				gv->window.draw(el->getText());
			}
		}
		gv->window.display();
	}
}

void graphicsSettingsMenu(GameVariable* gv) // graphics settings menu function.
{
	graphicsSettingsMenuUpdate(gv);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		gv->setMenuNum(0);

		for (auto& el : gv->buttonsVec) { el->getSprite().setFillColor(sf::Color::White); }
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

			if (gv->getIsFullscreen() == true && el->getName() == "fullscreenModeButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
			else if (gv->getIsFullscreen() == false && el->getName() == "windowedModeButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}

			if (gv->getGameLanguage() == 'e' && el->getName() == "engLangButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
			else if (gv->getGameLanguage() == 'r' && el->getName() == "rusLangButton")
			{
				el->getSprite().setFillColor(gv->greyColor);
			}
		}
		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y))
			{
				if (el->getSprite().getFillColor() != gv->greyColor)
				{
					el->getSprite().setFillColor(sf::Color::Yellow);

					if (el->getName() == "HDResolutionButton") { gv->setMenuNum(6); }
					if (el->getName() == "fullHDResolutionButton") { gv->setMenuNum(7); }
					if (el->getName() == "windowedModeButton") { gv->setMenuNum(8); }
					if (el->getName() == "fullscreenModeButton") { gv->setMenuNum(9); }
					if (el->getName() == "engLangButton") { gv->setMenuNum(10); }
					if (el->getName() == "rusLangButton") { gv->setMenuNum(11); }
					if (el->getName() == "backButton") { gv->setMenuNum(12); }
				}
			}
		}

		while (gv->window.pollEvent(gv->event))
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->setMenuNum(14);
				gv->buttonsVec.clear();
				gv->labelsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); gv->labelsVec.clear(); return; }
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->getMenuNum() > 0) { gv->buttonsVec.clear(); gv->labelsVec.clear(); return; }
		}
		gv->window.clear(sf::Color::Black);

		for (auto& el : gv->buttonsVec) { gv->window.draw(el->getSprite()); gv->window.draw(el->getText()); }
		for (auto& el : gv->labelsVec) { gv->window.draw(el->getText()); }

		gv->window.display();
	}
}

void settingsMenu(GameVariable* gv) // settings menu function.
{
	settingsMenuUpdate(gv);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		gv->setMenuNum(0);

		for (auto& el : gv->buttonsVec) { el->getSprite().setFillColor(sf::Color::White); }

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y))
			{
				el->getSprite().setFillColor(sf::Color::Yellow);
				if (el->getName() == "graphicsSettingsButton") { gv->setMenuNum(4); }
				if (el->getName() == "backButton") { gv->setMenuNum(5); }
			}
		}

		while (gv->window.pollEvent(gv->event))
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape)
			{
				gv->setMenuNum(13);
				gv->buttonsVec.clear();
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); return; }
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->getMenuNum() > 0) { gv->buttonsVec.clear(); return; }
		}
		gv->window.clear(sf::Color::Black);
		for (auto& el : gv->buttonsVec)
		{
			gv->window.draw(el->getSprite());
			gv->window.draw(el->getText());
		}
		gv->window.display();
	}
}

void mainMenu(GameVariable* gv, Entity*& player) // main menu function.
{
	mainMenuUpdate(gv, player);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		gv->setMenuNum(0);

		for (auto& el : gv->buttonsVec) { el->getSprite().setFillColor(sf::Color::White); }

		for (auto& el : gv->buttonsVec)
		{
			if (el->getSprite().getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) && el->getSprite().getFillColor() != gv->greyColor)
			{
				el->getSprite().setFillColor(sf::Color::Yellow);
				if (el->getName() == "singlePlayerButton") { gv->setMenuNum(1); }
				if (el->getName() == "settingsButton") { gv->setMenuNum(2); }
				if (el->getName() == "exitButton") { gv->setMenuNum(3); }
				if (el->getName() == "backToMenuButton") { gv->setMenuNum(15); }
				if (el->getName() == "continueButton") { gv->setMenuNum(23); }
				if (el->getName() == "restartGameButton") { gv->setMenuNum(1); }
				if (el->getName() == "multiPlayerButton") { gv->setMenuNum(17); }
			}
		}
		while (gv->window.pollEvent(gv->event))
		{
			if (gv->event.type == sf::Event::KeyPressed && gv->event.key.code == sf::Keyboard::Escape && (gv->getSinglePlayerGame() == true || gv->getMultiPlayerGame() == true))
			{
				gv->setMenuNum(23);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); gv->buttonsVec.clear(); return; }
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left && gv->getMenuNum() > 0)
			{
				if (gv->getMultiPlayerGame() == true && gv->getMenuNum() == 17)
				{
					gv->setMenuNum(23);
					gv->buttonsVec.clear();
					return;
				}
				else { gv->buttonsVec.clear(); return; }
			}
		}
		gv->window.clear(sf::Color::Black);
		for (auto& el : gv->buttonsVec) { gv->window.draw(el->getSprite()); gv->window.draw(el->getText()); }
		gv->window.display();
	}
}

void setMenuView(GameVariable* gv) // menu view setting function.
{
	gv->setViewSize(sf::Vector2f(static_cast<float>(gv->window.getSize().x), static_cast<float>(gv->window.getSize().y)));
	gv->setViewCenter(sf::Vector2f(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f));
	gv->window.setView(gv->getView());
}

void menuEventHandler(GameVariable* gv, Entity*& player) // function to handle menu events.
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	setMenuView(gv);
	mainMenu(gv, player);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		while (gv->window.pollEvent(gv->event)) { if (gv->event.type == sf::Event::Closed) { gv->window.close(); } }

		switch (gv->getMenuNum())
		{
		case 1:
			gv->setMenuNum(0);
			gv->setRestartGame(true);
			gv->setSinglePlayerGame(true);
			return;
		case 2:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 3:
			gv->setMenuNum(0);
			gv->window.close();
			return;
		case 4:
			gv->setMenuNum(0);
			graphicsSettingsMenu(gv);
			break;
		case 5:
			gv->setMenuNum(0);
			mainMenu(gv, player);
			break;
		case 6:
			gv->setMenuNum(0);
			if (gv->getIsFullscreen() == true) { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Fullscreen), settings; }
			else { gv->window.create(sf::VideoMode(1366, 768), "Bad Game", sf::Style::Close); }
			gv->window.setVerticalSyncEnabled(true);
			graphicsSettingsMenu(gv);
			break;
		case 7:
			gv->setMenuNum(0);
			if (gv->getIsFullscreen() == true) { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Fullscreen), settings; }
			else { gv->window.create(sf::VideoMode(1920, 1080), "Bad Game", sf::Style::Close); }
			gv->window.setVerticalSyncEnabled(true);
			graphicsSettingsMenu(gv);
			break;
		case 8:
			gv->setMenuNum(0);
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Close), settings;
			gv->window.setVerticalSyncEnabled(true);
			gv->setIsFullscreen(false);
			graphicsSettingsMenu(gv);
			break;
		case 9:
			gv->setMenuNum(0);
			gv->window.create(sf::VideoMode(gv->window.getSize().x, gv->window.getSize().y), "Bad Game", sf::Style::Fullscreen), settings;
			gv->window.setVerticalSyncEnabled(true);
			gv->setIsFullscreen(true);
			graphicsSettingsMenu(gv);
			break;
		case 10:
			gv->setMenuNum(0);
			gv->setGameLanguage('e');
			graphicsSettingsMenu(gv);
			break;
		case 11:
			gv->setMenuNum(0);
			gv->setGameLanguage('r');
			graphicsSettingsMenu(gv);
			break;
		case 12:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 13:
			gv->setMenuNum(0);
			mainMenu(gv, player);
			break;
		case 14:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 15:
			gv->setMenuNum(0);
			if (gv->getSinglePlayerGame() == true) { gv->setSinglePlayerGame(false); }
			if (gv->getMultiPlayerGame() == true) { gv->setMultiPlayerGame(false); }
			return;
		case 17:
			gv->setMenuNum(0);
			multiplayerMenu(gv);
			break;
		case 23:
			gv->setMenuNum(0);
			return;
		}
	}
}