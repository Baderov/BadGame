#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"
#include "CustomWidget.h"
#include "Minimap.h"
#include "Source.h"

void respawnEnemies(std::unique_ptr<GameVariable>& gv);

void respawnBoxes(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm);

void respawnHPBonuses(std::unique_ptr<GameVariable>& gv);

void restartGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm);

void drawGameResult(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm);

void singleplayerGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw,  Minimap& minimap);

#endif