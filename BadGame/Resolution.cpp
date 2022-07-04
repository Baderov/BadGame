#include "Resolution.h"

void graphicsSettingsMenuUpdate(GameVariables* gv)
{
	float winSizeX = gv->window.getSize().x;
	float winSizeY = gv->window.getSize().y;

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	if (gv->gameLanguage == 'e')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1366x768", round(winSizeX / 40.f), "HDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1920x1080", round(winSizeX / 40.f), "fullHDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"WINDOWED", round(winSizeX / 40.f), "windowedModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"FULLSCREEN", round(winSizeX / 40.f), "fullscreenModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"English", round(winSizeX / 40.f), "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"Ðóññêèé", round(winSizeX / 40.f), "rusLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 10.f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), L"BACK", round(winSizeX / 45.f), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 4.5f)), round(winSizeX / 27.f), "selectResolutionLabel"));
		gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 10.f)), round(winSizeX / 27.f), "selectWindowStyleLabel"));
		gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 32.f)), round(winSizeX / 27.f), "selectLanguageLabel"));
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1366x768", round(winSizeX / 40.f), "HDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.4f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 10.f), halfWinSizeY - round(winSizeX / 6.f)), L"1920x1080", round(winSizeX / 40.f), "fullHDResolutionButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"ÎÊÎÍÍÛÉ", round(winSizeX / 40.f), "windowedModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY - round(winSizeX / 21.f)), L"ÏÎËÍÎÝÊÐÀÍÍÛÉ", round(winSizeX / 40.f), "fullscreenModeButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"English", round(winSizeX / 40.f), "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 8.f), halfWinSizeY + round(winSizeX / 12.f)), L"Ðóññêèé", round(winSizeX / 40.f), "rusLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 10.f), round(winSizeY / 11.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), L"ÍÀÇÀÄ", round(winSizeX / 45.f), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"ÂÛÁÅÐÈÒÅ ÐÀÇÐÅØÅÍÈÅ ÝÊÐÀÍÀ", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 4.5f)), round(winSizeX / 27.f), "selectResolutionLabel"));
		gv->labelsVec.emplace_back(new Label(L"ÂÛÁÅÐÈÒÅ ÑÒÈËÜ ÎÊÍÀ", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 10.f)), round(winSizeX / 27.f), "selectWindowStyleLabel"));
		gv->labelsVec.emplace_back(new Label(L"ÂÛÁÅÐÈÒÅ ßÇÛÊ", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 32.f)), round(winSizeX / 27.f), "selectLanguageLabel"));
	}

}

void settingsMenuUpdate(GameVariables* gv)
{
	float winSizeX = gv->window.getSize().x;
	float winSizeY = gv->window.getSize().y;

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->buttonsVec.clear();
	if (gv->gameLanguage == 'e')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"GRAPHICS\nSETTINGS", round(winSizeX / 45.f), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"BACK", round(winSizeX / 45.f), "backButton", true));
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 6.5f), round(winSizeX / 12.75f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f)), L"ÍÀÑÒÐÎÉÊÈ\n ÃÐÀÔÈÊÈ", round(winSizeX / 45.f), "graphicsSettingsButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 9.5f), round(winSizeX / 19.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f)), L"ÍÀÇÀÄ", round(winSizeX / 45.f), "backButton", true));
	}
}

void mainMenuUpdate(GameVariables* gv, Entity*& player)
{
	float winSizeX = gv->window.getSize().x;
	float winSizeY = gv->window.getSize().y;

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->buttonsVec.clear();
	if (gv->gameLanguage == 'e')
	{
		if (gv->singlePlayerGame == false && gv->multiPlayerGame == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"SINGLEPLAYER", round(winSizeX / 45.f), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"MULTIPLAYER", round(winSizeX / 45.f), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", round(winSizeX / 45.f), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", round(winSizeX / 45.f), "exitButton", true));
		}
		else if (gv->singlePlayerGame == true && gv->multiPlayerGame == false)
		{
			if (player == nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"RESTART", round(winSizeX / 45.f), "restartGameButton", true));
			}
			else if (player != nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"CONTINUE", round(winSizeX / 45.f), "continueButton", true));
			}
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"BACK TO MENU", round(winSizeX / 45.f), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"SETTINGS", round(winSizeX / 45.f), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"EXIT", round(winSizeX / 45.f), "exitButton", true));

		}
	}
	else if (gv->gameLanguage == 'r')
	{
		if (gv->singlePlayerGame == false && gv->multiPlayerGame == false)
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"ÎÄÈÍÎ×ÍÀß ÈÃÐÀ", round(winSizeX / 45.f), "singlePlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"ÑÅÒÅÂÀß ÈÃÐÀ", round(winSizeX / 45.f), "multiPlayerButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"ÍÀÑÒÐÎÉÊÈ", round(winSizeX / 45.f), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"ÂÛÕÎÄ", round(winSizeX / 45.f), "exitButton", true));
		}
		else if (gv->singlePlayerGame == true && gv->multiPlayerGame == false)
		{
			if (player == nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"ÏÅÐÅÇÀÏÓÑÊ", round(winSizeX / 45.f), "restartGameButton", true));
			}
			else if (player != nullptr)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f)), L"ÏÐÎÄÎËÆÈÒÜ", round(winSizeX / 45.f), "continueButton", true));
			}
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"ÍÀÇÀÄ Â ÌÅÍÞ", round(winSizeX / 45.f), "backToMenuButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f)), L"ÍÀÑÒÐÎÉÊÈ", round(winSizeX / 45.f), "settingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.8f), round(winSizeY / 10.5f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f)), L"ÂÛÕÎÄ", round(winSizeX / 45.f), "exitButton", true));
		}
	}
}

void multiplayerMenuUpdate(GameVariables* gv)
{
	float winSizeX = gv->window.getSize().x;
	float winSizeY = gv->window.getSize().y;

	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;

	gv->buttonsVec.clear();
	gv->labelsVec.clear();

	if (gv->gameLanguage == 'e')
	{
		gv->labelsVec.emplace_back(new Label(L"ENTER NICKNAME", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 9.1f)), round(winSizeX / 38.f), "enterNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 12.75f)), L"", round(winSizeX / 43.f), "nicknameFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ENTER IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 32.f)), round(winSizeX / 38.f), "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"", round(winSizeX / 43.f), "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ENTER PORT", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 21.f)), round(winSizeX / 38.f), "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 12.75f)), L"", round(winSizeX / 43.f), "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Connect", round(winSizeX / 64.f), "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Back", round(winSizeX / 64.f), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), round(winSizeX / 38.f), "errorLabel"));
		gv->labelsVec.back()->getText().setFillColor(sf::Color::Red);
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->labelsVec.emplace_back(new Label(L"ÂÂÅÄÈÒÅ ÍÈÊÍÅÉÌ", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 9.1f)), round(winSizeX / 38.f), "enterNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 12.75f)), L"", round(winSizeX / 43.f), "nicknameFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ÂÂÅÄÈÒÅ IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - round(winSizeX / 32.f)), round(winSizeX / 38.f), "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY), L"", round(winSizeX / 43.f), "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ÂÂÅÄÈÒÅ ÏÎÐÒ", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 21.f)), round(winSizeX / 38.f), "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 4.6f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 12.75f)), L"", round(winSizeX / 43.f), "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX - round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Âîéòè", round(winSizeX / 64.f), "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(round(winSizeX / 12.75f), round(winSizeX / 38.f)), sf::Vector2f(halfWinSizeX + round(winSizeX / 19.f), halfWinSizeY + round(winSizeX / 7.6f)), L"Íàçàä", round(winSizeX / 64.f), "backButton", true));

		gv->labelsVec.emplace_back(new Label(L"", sf::Vector2f(halfWinSizeX, halfWinSizeY + round(winSizeX / 5.f)), round(winSizeX / 38.f), "errorLabel"));
		gv->labelsVec.back()->getText().setFillColor(sf::Color::Red);
	}
}