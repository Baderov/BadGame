#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include "Variables.h" // header file for global variables.
#include "Network.h" // header file for working with the network.
#include "GameUpdate.h" // game update header file.
#include "Keyboard.h" // header file for handling keyboard events.
#include "Chat.h" // header file for working with chat.

void errorChecking(GameVariables* gv); // error checking function.

void multiplayerMenu(GameVariables* gv); // multiplayer menu function.

void graphicsSettingsMenu(GameVariables* gv); // graphics settings menu function.

void settingsMenu(GameVariables* gv); // settings menu function.

void mainMenu(GameVariables* gv, Entity*& player); // main menu function.

void menuEventHandler(GameVariables* gv, Entity*& player); // menu event handling function.