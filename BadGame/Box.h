#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.
#include "Entity.h" // подключаем заголовочный файл.

class Box : public Entity // создаём класс коробки и наследуем его от Entity.
{
public:
	Box(sf::Image& image, sf::Vector2f startPos,  std::wstring name); // конструктор класса.
	void update(GameVariables* gv); // функция обновления логики объекта. (в параметрах передаем время).
	void move(GameVariables* gv);
};