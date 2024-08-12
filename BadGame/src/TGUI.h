#ifndef TGUI_H
#define TGUI_H

#include "SingleplayerManager.h"
#include "Minimap.h"
#include "Menu.h"
#include "Source.h"
#include "CustomWidget.h"
enum class WidgetState
{
	Nothing, ResolutionComboBoxChanged, LanguageComboBoxChanged, FPSComboBoxChanged, FullscreenCheckBoxChanged, VsyncCheckBoxChanged
}; inline WidgetState widgetState;

void widgetStateHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw);

void menuApplyButtonPressed(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap);

void graphicsSettingsMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap);

void settingsMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw);

void multiplayerMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void multiplayerGameUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void menuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<CustomWidget>& cw);

#endif