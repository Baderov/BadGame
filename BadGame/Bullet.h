#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Entity.h" // подключаем заголовочный файл.

class Bullet : public Entity // создаём класс пули и наследуем его от Entity.
{
public:
	Bullet(sf::Image& image, sf::Vector2f startPos, std::string name, std::string creatorName, sf::Vector2f aimPos); // конструктор класса.
	void update(GameVariables* gv); // функция обновления логики объекта. (в параметрах передаем время).
	void move(GameVariables* gv);
};