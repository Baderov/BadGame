#ifndef MENU_H
#define MENU_H

#include "ObjectPool.hpp"
#include "TGUI.h"
#include "Network.h"
#include "GameUpdate.h"
#include "Minimap.h"
#include "MenuBackground.h"

inline MenuBackground menuBackground;

enum class MultiplayerMenuErrors
{
	NoErrors, ServerIsNotAvailable, NicknameIsAlreadyTaken, NickMustContainMoreChars, WrongIP, WrongPort
}; inline MultiplayerMenuErrors multiplayerMenuError;

enum class MenuAction
{
	Nothing, OpenMainMenu, OpenGameMenu, OpenMultiplayerMenu, OpenSettingsMenu, OpenGraphicsSettingsMenu, StartGame, RestartGame, ContinueGame
}; inline MenuAction menuAction;

void errorChecking(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void updateFields(std::unique_ptr<NetworkManager>& nm);

void updateMenu(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap);

void openMenu(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap);

void menuEventHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap, MenuType _menuType);

#endif