#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "GameUpdate.h" // game update header file.
#include "Console.h" // header file for working with the console.
#include "Item.h" // header file for items.
#include "Menu.h" // header file for working with the menu.
#include "Minimap.h" // header file for minimap.

void updateFPS(GameVariable* gv); // FPS update function.

void s_eventHandler(GameVariable* gv, Minimap& minimap); // event handling function for singleplayer.

void s_resetVariables(GameVariable* gv); // global variable reset function for singleplayer.

void singleplayerGame(GameVariable* gv, Minimap& minimap); // singleplayer launch function.

void logsFunc(GameVariable* gv); // function for logs in DEBUG mode.

int main(); // the main function of the program.