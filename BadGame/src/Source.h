#ifndef SOURCE_H
#define SOURCE_H

#include "Singleplayer.h"
#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"
#include "CustomWidget.h"
#include "Console.h"
#include "Menu.h"

//void logsFunc(std::unique_ptr<SingleplayerManager>& sm); // function for logs in DEBUG mode.

void initObjects(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);

void resetObjects(std::unique_ptr<SingleplayerManager>& sm);

int main();

#endif