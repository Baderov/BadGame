#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include "Variables.h" // header file for global variables.
#include "Network.h" // header file for working with the network.
#include "GameUpdate.h" // game update header file.
#include "Chat.h" // header file for working with chat.
#include "Minimap.h" // header file for minimap.

void errorChecking(GameVariable* gv, int& countOfDotsInIP); // error checking function.

void updateFields(GameVariable* gv); // function for update fields in multiplayer menu.

void multiplayerMenu(GameVariable* gv); // multiplayer menu function.

void graphicsSettingsMenu(GameVariable* gv, Minimap& minimap); // graphics settings menu function.

void settingsMenu(GameVariable* gv); // settings menu function.

void mainMenu(GameVariable* gv); // main menu function.

void menuEventHandler(GameVariable* gv, Minimap& minimap); // menu event handling function.