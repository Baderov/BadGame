#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Entity.h" // подключаем заголовочный файл.

class Enemy : public Entity // создаём класс игрока и наследуем его от Entity.
{
public:
	Enemy(sf::Image& image, sf::Vector2f startPos, std::wstring name); // конструктор класса.
	void update(GameVariables* gv);
	void move(GameVariables* gv);
	void rotate();
};