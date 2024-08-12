#ifndef CUSTOM_WIDGET_H
#define CUSTOM_WIDGET_H

#include "GameVariable.h"
#include "GameWindow.h"

class CustomWidget
{
private:
	std::mutex mtx;
	tgui::Font tguiFont;
	GameLanguage tempGameLanguage;
	sf::Vector2u tempWindowSize;
	unsigned int tempFPSLimiter;
	bool tempIsFullscreen;
	bool tempIsVsync;
public:
	tgui::Gui gameGUI;
	tgui::Gui menuGUI;

	CustomWidget(std::unique_ptr<GameWindow>& gw);
	void updateGUI(std::unique_ptr<GameWindow>& gw);

	GameLanguage getTempGameLanguage();
	sf::Vector2u getTempWindowSize();
	unsigned int getTempFPSLimiter();
	bool getTempIsFullscreen();
	bool getTempIsVsync();

	void setTempGameLanguage(GameLanguage tempGameLanguage);
	void setTempWindowSize(sf::Vector2u tempWindowSize);
	void setTempFPSLimiter(unsigned int tempFPSLimiter);
	void setTempIsFullscreen(bool tempIsFullscreen);
	void setTempIsVsync(bool tempIsVsync);

	// MultiplayerMenu.
	void enableMultiplayerMenuWidgets();
	void disableMultiplayerMenuWidgets();

	// Button.
	bool connectButtonIsEnabled();

	// Label.
	void setErrorLabelText(tgui::String&& text);

	// EditBox.
	void updateEditBox();
	void setEditBoxVisible(bool&& isVisible);
	void setEditBoxEnabled(bool&& isEnabled);
	void setEditBoxText(tgui::String&& text);
	bool editBoxIsReadOnly();
	bool editBoxIsVisible();
	const tgui::String& getEditBoxText();

	// ListView.
	size_t addClientToPlayersList(std::wstring& clientNick);
	void removeClientFromPlayersList(size_t&& clientID);
	void changeItemInPlayersList(size_t&& clientID, std::wstring&& clientNick, std::wstring&& ping);
	void updatePlayersList(GameLanguage&& gameLanguage);
	void setPlayersListVisible(bool&& isVisible);

	// ChatBox.
	void addLineToChatBox(tgui::String&& text, tgui::Color&& color);
	void setChatBoxVisible(bool&& isVisible);
	void setChatBoxEnabled(bool&& isEnabled);
	bool chatBoxIsVisible();

	// GUI.
	void handleGameGUIEvent(sf::Event& event);
	void drawGameGUI();
};


#endif