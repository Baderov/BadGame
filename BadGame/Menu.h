#ifndef MENU_H
#define MENU_H

#include "ObjectPool.hpp"
#include "TGUI.h"
#include "Network.h" // header file for working with the network.
#include "GameUpdate.h" // game update header file.
#include "Chat.h" // header file for working with chat.
#include "Minimap.h" 
#include "PlayersList.h"

enum class MultiplayerErrors // enumeration for menu errors.
{
	NoErrors, ServerIsNotAvailable, NicknameIsAlreadyTaken, NickMustContainMoreChars, WrongIP, WrongPort
};

inline MultiplayerErrors multiplayerError;

void errorChecking(std::unique_ptr<GameVariable>& gv, int& countOfDotsInIP); // error checking function.

void updateFields(std::unique_ptr<GameVariable>& gv); // function for update fields in multiplayer menu.

void multiplayerMenu(std::unique_ptr<GameVariable>& gv, PlayersList& playersList, Chat& chat); // multiplayer menu function.

void graphicsSettingsMenu(std::unique_ptr<GameVariable>& gv, Minimap& minimap); // graphics settings menu function.

void settingsMenu(std::unique_ptr<GameVariable>& gv); // settings menu function.

void mainMenu(std::unique_ptr<GameVariable>& gv); // main menu function.

void menuEventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // function to handle menu events.

#endif