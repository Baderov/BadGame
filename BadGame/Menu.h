#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include "Variables.h" // header file for global variables.
#include "Network.h" // header file for working with the network.
#include "GameUpdate.h" // game update header file.
#include "Keyboard.h" // header file for handling keyboard events.
#include "Chat.h" // header file for working with chat.

void errorChecking(GameVariable* gv); // error checking function.

void updateFields(GameVariable* gv); // function for update fields in multiplayer menu.

void multiplayerMenu(GameVariable* gv); // multiplayer menu function.

void graphicsSettingsMenu(GameVariable* gv); // graphics settings menu function.

void settingsMenu(GameVariable* gv); // settings menu function.

void mainMenu(GameVariable* gv, Entity*& player); // main menu function.

void menuEventHandler(GameVariable* gv, Entity*& player); // menu event handling function.