#include "Resolution.h"

void graphicsSettingsMenuUpdate(GameVariables* gv)
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	if (gv->gameLanguage == 'e')
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
	else if (gv->gameLanguage == 'r')
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

void settingsMenuUpdate(GameVariables* gv)
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->buttonsVec.clear();
	if (gv->gameLanguage == 'e')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"GRAPHICS\nSETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"BACK", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"Õ¿—“–Œ… »\n √–¿‘» »", static_cast<unsigned int>(round(winSizeX / 45.f)), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"Õ¿«¿ƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backButton", true));
	}
}

void mainMenuUpdate(GameVariables* gv, Entity*& player)
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;
	gv->buttonsVec.clear();
	if (gv->gameLanguage == 'e')
	{
		if (gv->singlePlayerGame == false && gv->multiPlayerGame == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"SINGLEPLAYER", static_cast<unsigned int>(round(winSizeX / 45.f)), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"MULTIPLAYER", static_cast<unsigned int>(round(winSizeX / 45.f)), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
		else if (gv->singlePlayerGame == true && gv->multiPlayerGame == false)
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
		else if (gv->singlePlayerGame == false && gv->multiPlayerGame == true)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"CONTINUE", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"BACK TO MENU", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
	}
	else if (gv->gameLanguage == 'r')
	{
		if (gv->singlePlayerGame == false && gv->multiPlayerGame == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"Œƒ»ÕŒ◊Õ¿ﬂ »√–¿", static_cast<unsigned int>(round(winSizeX / 45.f)), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"—≈“≈¬¿ﬂ »√–¿", static_cast<unsigned int>(round(winSizeX / 45.f)), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"Õ¿—“–Œ… »", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"¬€’Œƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
		else if (gv->singlePlayerGame == true && gv->multiPlayerGame == false)
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
		else if (gv->singlePlayerGame == false && gv->multiPlayerGame == true)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"œ–ŒƒŒÀ∆»“‹", static_cast<unsigned int>(round(winSizeX / 45.f)), "continueButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"Õ¿«¿ƒ ¬ Ã≈Õﬁ", static_cast<unsigned int>(round(winSizeX / 45.f)), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"Õ¿—“–Œ… »", static_cast<unsigned int>(round(winSizeX / 45.f)), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"¬€’Œƒ", static_cast<unsigned int>(round(winSizeX / 45.f)), "exitButton", true));
		}
	}
}

void multiplayerMenuUpdate(GameVariables* gv)
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);

	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();

	if (gv->gameLanguage == 'e')
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
	else if (gv->gameLanguage == 'r')
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