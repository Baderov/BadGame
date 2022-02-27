#pragma once // защита от повторного включения.
#include "GameUpdate.h" // подключаем библиотеку.

void authKeyboard(GameVariables* gv, sf::Event& event, sf::Text& nicknameText, bool& input); // функция обновления клавиш во время авторизации.