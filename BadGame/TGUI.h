#ifndef TGUI_H
#define TGUI_H

#include "Variables.h"
#include "Minimap.h"

void applyButtonPressed(std::unique_ptr<GameVariable>& gv, Minimap& minimap);

void graphicsSettingsMenuUpdate(std::unique_ptr<GameVariable>& gv, Minimap& minimap); // graphic settings menu update function.

void settingsMenuUpdate(std::unique_ptr<GameVariable>& gv); // settings menu update function.

void multiplayerMenuUpdate(std::unique_ptr<GameVariable>& gv); // multiplayer menu update function.

void mainMenuUpdate(std::unique_ptr<GameVariable>& gv); // main menu update function.

#endif
