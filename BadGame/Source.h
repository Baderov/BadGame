#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.
#include "Text.h" // header file for working with text.
#include "GameUpdate.h" // game update header file.
#include "Console.h" // header file for working with the console.
#include "Item.h" // header file for items.
#include "Menu.h" // header file for working with the menu.

void updateTime(GameVariables* gv); // time update function.

void updateFPS(GameVariables* gv); // FPS update function.

void eventHandler(sf::Event& event, GameVariables* gv); // event handling function.

void singleplayerGame(GameVariables* gv); // single player launch function.

int main(); // the main function of the program.