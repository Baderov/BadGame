#ifndef SERVER_IS_NOT_AVAILABLE_H
#define SERVER_IS_NOT_AVAILABLE_H

#include "SingleplayerManager.h"
#include "Network.h"

void setServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);

void updateServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);

void drawServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm);

#endif