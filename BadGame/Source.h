#pragma once // used to provide additional control at compile time.
#include "GameUpdate.h" // game update header file.
#include "Console.h" // header file for working with the console.
#include "Item.h" // header file for items.
#include "Menu.h" // header file for working with the menu.
#include "Chat.h" // header file for working with chat.
#include "Minimap.h" // header file for minimap.
#include "PlayersList.h"

void updateFPS(GameVariable* gv); // FPS update function.

void s_eventHandler(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // event handling function for singleplayer.

void singleplayerGame(GameVariable* gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // singleplayer launch function.

void logsFunc(GameVariable* gv); // function for logs in DEBUG mode.

int main(); // the main function of the program.