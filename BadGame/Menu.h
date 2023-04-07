#pragma once // used to provide additional control at compile time.
#include "Network.h" // header file for working with the network.
#include "GameUpdate.h" // game update header file.
#include "Chat.h" // header file for working with chat.
#include "Minimap.h" // header file for minimap.
#include "PlayersList.h"

void errorChecking(GameVariable* gv, int& countOfDotsInIP); // error checking function.

void updateFields(GameVariable* gv); // function for update fields in multiplayer menu.

void multiplayerMenu(GameVariable* gv, PlayersList& playersList, Chat& chat); // multiplayer menu function.

void graphicsSettingsMenu(GameVariable* gv, Minimap& minimap); // graphics settings menu function.

void settingsMenu(GameVariable* gv); // settings menu function.

void mainMenu(GameVariable* gv); // main menu function.

void menuEventHandler(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // function to handle menu events.