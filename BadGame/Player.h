#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Entity.h" // подключаем заголовочный файл.

class Player : public Entity // создаём класс игрока и наследуем его от Entity.
{
public:
	Player(sf::Image& image, sf::Vector2f startPos, std::wstring name); // конструктор класса.
	void update(GameVariables* gv);
	void move(GameVariables* gv);
	void rotate(GameVariables* gv);
	void updateLaser(GameVariables* gv);
	void updateReloadRect();
};