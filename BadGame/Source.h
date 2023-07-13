#ifndef SOURCE_H
#define SOURCE_H

#include "ObjectPool.hpp"
#include "Variables.h"
#include "Console.h" // header file for working with the console.
#include "Menu.h" // header file for working with the menu.

//void logsFunc(std::unique_ptr<GameVariable>& gv); // function for logs in DEBUG mode.

void updateFPS(sf::Time& fpsPreviousTime, sf::Time& fpsCurrentTime, sf::Clock& fpsClock, float& fps); // FPS update function.

void initObjects(std::unique_ptr<GameVariable>& gv);

void singleplayerGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat); // singleplayer launch function.

int main(); // the main function of the program.

#endif