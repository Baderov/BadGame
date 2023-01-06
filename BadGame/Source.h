#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Text.h" // header file for working with text.
#include "GameUpdate.h" // game update header file.
#include "Console.h" // header file for working with the console.
#include "Item.h" // header file for items.
#include "Menu.h" // header file for working with the menu.

void updateFPS(GameVariable* gv); // FPS update function.

void eventHandlerSingleplayer(GameVariable* gv); // event handling function.

void singleplayerGame(GameVariable* gv); // single player launch function.

void logsFunc(GameVariable* gv); // function for logs in DEBUG mode.

int main(); // the main function of the program.