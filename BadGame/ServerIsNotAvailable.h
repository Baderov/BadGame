#ifndef SERVER_IS_NOT_AVAILABLE_H
#define SERVER_IS_NOT_AVAILABLE_H

#include "Variables.h"
#include "Chat.h"

void setServerIsNotAvailable(std::unique_ptr<GameVariable>& gv);

void updateServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, Chat& chat);

void drawServerIsNotAvailable(std::unique_ptr<GameVariable>& gv);

#endif