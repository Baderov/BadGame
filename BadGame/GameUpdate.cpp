#include "GameUpdate.h" // game update header file.

void graphicsSettingsMenuUpdate(GameVariable* gv) // graphic settings menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	if (gv->getGameLanguage() == 'e')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1366x768", static_cast<unsigned int>(round(winSizeX / 40.f)), "HDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1920x1080", static_cast<unsigned int>(round(winSizeX / 40.f)), "fullHDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"WINDOWED", static_cast<unsigned int>(round(winSizeX / 40.f)), "windowedModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"FULLSCREEN", static_cast<unsigned int>(round(winSizeX / 40.f)), "fullscreenModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"English", static_cast<unsigned int>(round(winSizeX / 40.f)), "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"–ÛÒÒÍËÈ", static_cast<unsigned int>(round(winSizeX / 40.f)), "rusLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 10.f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), L"BACK", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 4.5f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectResolutionLabel"));
		gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 10.f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectWindowStyleLabel"));
		gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 32.f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectLanguageLabel"));
	}
	else if (gv->getGameLanguage() == 'r')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1366x768", static_cast<unsigned int>(round(winSizeX / 40.f)), "HDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1920x1080", static_cast<unsigned int>(round(winSizeX / 40.f)), "fullHDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"Œ ŒÕÕ€…", static_cast<unsigned int>(round(winSizeX / 40.f)), "windowedModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"œŒÀÕŒ› –¿ÕÕ€…", static_cast<unsigned int>(round(winSizeX / 40.f)), "fullscreenModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"English", static_cast<unsigned int>(round(winSizeX / 40.f)), "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"–ÛÒÒÍËÈ", static_cast<unsigned int>(round(winSizeX / 40.f)), "rusLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 10.f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), L"Õ¿«¿ƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ –¿«–≈ÿ≈Õ»≈ › –¿Õ¿", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 4.5f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectResolutionLabel"));
		gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ —“»À‹ Œ Õ¿", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 10.f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectWindowStyleLabel"));
		gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ ﬂ«€ ", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 32.f)), static_cast<unsigned int>(round(winSizeX / 27.f)), "selectLanguageLabel"));
	}

}

void settingsMenuUpdate(GameVariable* gv) // settings menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->buttonsVec.clear();
	if (gv->getGameLanguage() == 'e')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"GRAPHICS\nSETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"BACK", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));
	}
	else if (gv->getGameLanguage() == 'r')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"Õ¿—“–Œ… »\n √–¿‘» »", static_cast<unsigned int>(round(winSizeX / 45.f)), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"Õ¿«¿ƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));
	}
}

void mainMenuUpdate(GameVariable* gv, Entity*& player) // main menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;
	gv->buttonsVec.clear();
	if (gv->getGameLanguage() == 'e')
	{
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"SINGLEPLAYER", static_cast<unsigned int>(round(winSizeX / 45.f)), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"MULTIPLAYER", static_cast<unsigned int>(round(winSizeX / 45.f)), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
		else if (gv->getSinglePlayerGame() == true && gv->getMultiPlayerGame() == false)
		{
			if (player == nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"RESTART", static_cast<unsigned int>(round(winSizeX / 45.f)), "restartGameButton", true));
			}
			else if (player != nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"CONTINUE", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			}
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"BACK TO MENU", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));

		}
		else if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == true)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"CONTINUE", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"BACK TO MENU", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
	}
	else if (gv->getGameLanguage() == 'r')
	{
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"Œƒ»ÕŒ◊Õ¿ﬂ »√–¿", static_cast<unsigned int>(round(winSizeX / 45.f)), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"—≈“≈¬¿ﬂ »√–¿", static_cast<unsigned int>(round(winSizeX / 45.f)), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"Õ¿—“–Œ… »", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"¬€’Œƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
		else if (gv->getSinglePlayerGame() == true && gv->getMultiPlayerGame() == false)
		{
			if (player == nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"œ≈–≈«¿œ”— ", static_cast<unsigned int>(round(winSizeX / 45.f)), "restartGameButton", true));
			}
			else if (player != nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"œ–ŒƒŒÀ∆»“‹", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			}
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"Õ¿«¿ƒ ¬ Ã≈Õﬁ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"Õ¿—“–Œ… »", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"¬€’Œƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
		else if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == true)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"œ–ŒƒŒÀ∆»“‹", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"Õ¿«¿ƒ ¬ Ã≈Õﬁ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"Õ¿—“–Œ… »", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"¬€’Œƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
	}
}

void multiplayerMenuUpdate(GameVariable* gv) // multiplayer menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();

	if (gv->getGameLanguage() == 'e')
	{
		gv->labelsVec.emplace_back(new Label(L"ENTER NICKNAME", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 9.1f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 12.75f)), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "nicknameFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ENTER IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 32.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ENTER PORT", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 21.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 12.75f)), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Connect", static_cast<unsigned int>(round(winSizeX / 64.f)), "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Back", static_cast<unsigned int>(round(winSizeX / 64.f)), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "errorLabel"));
		gv->labelsVec.back()->getText().setFillColor(sf::Color::Red);
	}
	else if (gv->getGameLanguage() == 'r')
	{
		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ Õ» Õ≈…Ã", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 9.1f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 12.75f)), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "nicknameFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 32.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ œŒ–“", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 21.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 12.75f)), L"", static_cast<unsigned int>(round(winSizeX / 43.f)), "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"¬ÓÈÚË", static_cast<unsigned int>(round(winSizeX / 64.f)), "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Õ‡Á‡‰", static_cast<unsigned int>(round(winSizeX / 64.f)), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), static_cast<unsigned int>(round(winSizeX / 38.f)), "errorLabel"));
		gv->labelsVec.back()->getText().setFillColor(sf::Color::Red);
	}
}

void boxSpawn(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities) // box spawn function.
{
	for (int i = 0; i < std::size(gv->boxStartPositions); i++)
	{
		entities.emplace_back(new Box(gv->boxImage, sf::Vector2f(gv->boxStartPositions[i]), L"Box")); // create a box and send it to the end of the list.
	}
}

void restartGame(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, Entity*& player) // game restart function.
{
	entities.clear();

	gv->setNumberOfPlayers(0);
	gv->setNumberOfEnemies(0);
	gv->setMenuTimer(0.f);

	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 0.f), L"LeftWall")); // create a left wall and throw it into the list of entities.
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(3000.f, 0.f), L"RightWall")); // create a right wall and throw it into the list of entities.
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 0.f), L"TopWall")); // create a top wall and throw it into the list of entities.
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 2936.f), L"BottomWall")); // create a bottom wall and throw it into the list of entities.
	entities.emplace_back(new Player(gv->playerImage, sf::Vector2f(gv->getPlayerStartPos()), gv->getNickname())); // create a player and throw it into the list of entities.
	player = entities.back().get(); // assign the value of the pointer to the player.

	for (int i = 0; i < 10 + rand() % 21; i++)
	{
		entities.emplace_back(new Enemy(gv->enemyImage, sf::Vector2f(static_cast<float>(100 + rand() % 2600), static_cast<float>(100 + rand() % 2600)), L"Enemy"));
		gv->setNumberOfEnemies(gv->getNumberOfEnemies() + 1);
	}

	for (int i = 0; i < 20 + rand() % 31; i++)
	{
		entities.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(static_cast<float>(100 + rand() % 2600), static_cast<float>(100 + rand() % 2600)), L"HPBonus"));
	}

	gv->setNumberOfPlayers(gv->getNumberOfPlayers() + 1);
	boxSpawn(gv, entities);
}

void updateEntities(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2, Entity*& player) // entity update function. 
{
	for (it = entities.begin(); it != entities.end();) // iterate through the list from beginning to end.
	{
		Entity* entity = (*it).get(); // create a pointer object and assign the value of the first iterator to make the code easier to read.
		if (player == nullptr && dynamic_cast<Enemy*>(entity))
		{
			entity->setIsAlive(false);
		}
		for (it2 = entities.begin(); it2 != entities.end(); it2++) // iterate through the list from beginning to end.
		{
			Entity* entity2 = (*it2).get(); // create a pointer object and assign the value of the first iterator to make the code easier to read.
			collisionHandler(entity, entity2); // calling the collision handling function.	
			if (dynamic_cast<Enemy*>(entity) && dynamic_cast<Player*>(entity2))
			{
				entity->setAimPos(entity2->getCurrentPos());
			}
		}

		if (player != nullptr && player->getCurrentAmmo() < 30 && player->getIsReload() == true && player->getReloadTime() >= 2.f)
		{
			player->setMissingAmmo(player->getMagazineAmmo() - player->getCurrentAmmo());
			if (player->getMaxAmmo() < player->getMagazineAmmo())
			{
				player->setCurrentAmmo(player->getCurrentAmmo() + player->getMaxAmmo());
				player->setMaxAmmo(0);
			}
			else
			{
				player->setCurrentAmmo(player->getCurrentAmmo() + player->getMissingAmmo());
				player->setMaxAmmo(player->getMaxAmmo() - player->getMissingAmmo());
			}

			player->setIsReload(false);
		}

		if (gv->getNumberOfEnemies() == 0 && player != nullptr)
		{
			int gc = player->getGoldCoins();
			restartGame(gv, entities, player);
			player->setGoldCoins(gc);
			return;
		}
		if (entity->getIsShoot() == true)
		{
			if (dynamic_cast<Player*>(entity)) // if the entity is a player.
			{
				if (entity->getCurrentAmmo() > 0 && player->getIsReload() == false)
				{
					entities.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), L"Bullet", entity->getName(), gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)))); // create a bullet and send it to the end of the list.
					entity->setCurrentAmmo(entity->getCurrentAmmo() - 1);
				}
				entity->setIsShoot(false);
			}
			if (dynamic_cast<Enemy*>(entity)) // if the entity is an enemy.
			{
				float distance = sqrt(((entity->getAimPos().x - entity->getCurrentPos().x) * (entity->getAimPos().x - entity->getCurrentPos().x)) + ((entity->getAimPos().y - entity->getCurrentPos().y) * (entity->getAimPos().y - entity->getCurrentPos().y)));
				if (distance < 750.f)
				{
					entities.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), L"Bullet", entity->getName(), entity->getAimPos())); // create a bullet and send it to the end of the list.
				}
				entity->setIsShoot(false);
			}
		}

		entity->update(gv); // call the update function for all entities.
		if (entity->getIsAlive() == false) // if entity is dead.
		{
			if (dynamic_cast<Box*>(entity)) // if the entity is a Box.
			{
				int itemNum = 0 + rand() % 3;
				{
					if (itemNum == 1)
					{
						for (int i = 0; i < 0 + rand() % 2; i++)
						{
							entities.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"HPBonus"));
						}
					}
					else if (itemNum == 2)
					{
						for (int i = 0; i < 0 + rand() % 3; i++)
						{
							entities.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"GoldCoin"));
						}
					}
				}
			}
			if (dynamic_cast<Player*>(entity)) // if the entity is a player.
			{
				gv->setNumberOfPlayers(gv->getNumberOfPlayers() - 1);
				player = nullptr;
			}
			if (dynamic_cast<Enemy*>(entity)) // if the entity is an enemy.
			{
				gv->setNumberOfEnemies(gv->getNumberOfEnemies() - 1);
				for (int i = 0; i < 0 + rand() % 6; i++)
				{
					entities.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"GoldCoin"));
				}
			}
			it = entities.erase(it); // remove list item.
		}
		else it++; // move on to the next entity.
	}
}

void drawEntities(GameVariable* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it) // entity drawing function.
{
	for (it = entities.begin(); it != entities.end(); it++) // iterate through the list from beginning to end.
	{
		if (gv->getShowHitbox() == true) // if we show hitboxes.
		{
			gv->window.draw((*it)->getRectHitbox()); // draw rectangular hitboxes.
		}
		else
		{
			gv->window.draw((*it)->getSprite()); // draw entity sprites.
		}

		if ((*it)->getIsMove() == true && dynamic_cast<Player*>((*it).get())) // if the player is moving.
		{
			gv->window.draw(gv->playerDestination); // draw a label.
		}
		if (gv->getShowAimLaser() == true && gv->getFocusEvent() == true && dynamic_cast<Player*>((*it).get())) // if we show the aiming laser.
		{
			gv->window.draw(gv->aimLaser); // draw aiming laser.
		}
	}
	for (it = entities.begin(); it != entities.end(); it++) // iterate through the list from beginning to end.
	{
		if (dynamic_cast<Player*>((*it).get()) || dynamic_cast<Enemy*>((*it).get())) // if the entity is a player or enemy.
		{
			gv->window.draw((*it)->getHPBarOuter());
			gv->window.draw((*it)->getHPBarInner());
			if ((*it)->getIsReload() == true) // if the entity is reloading.
			{
				gv->window.draw((*it)->getReloadRectOuter());
				gv->window.draw((*it)->getReloadRectInner());
				gv->window.draw((*it)->getReloadText());
			}
			gv->window.draw((*it)->getHPText());
			gv->window.draw((*it)->getNameText());
		}
	}
}