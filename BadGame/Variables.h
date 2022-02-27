#pragma once // защита от повторного включения.
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <memory>
#include <cmath> 
#include <list>

struct GameVariables // объявляем структуру для игровых переменных.
{
	sf::RenderWindow window; // главное окно приложения.

	sf::Image playerImage; // картинка игрока.
	sf::Image enemyImage; // картинка врага.
	sf::Image wallImage; // картинка стены.
	sf::Image bulletImage; // картинка пули.
	sf::Image boxImage; // картинка коробки.
	sf::Image goldCoinImage; // картинка пули.
	sf::Image goldCoinHUDImage; // картинка пули.
	sf::Image hpBonusImage; // картинка коробки.

	sf::Texture goldCoinHUDTexture;

	sf::Sprite goldCoinHUDSprite;

	sf::RectangleShape aimLaser; // прицельный лазер.

	sf::CircleShape playerDestination; // создаём метку передвижения игрока.

	sf::View view;

	sf::Font consolasFont; // создаём объект шрифта Consolas.
	
	sf::Text gameInfoText; // текст игровой информации.
	sf::Text playerInfoText; // текст информации об игроке.
	sf::Text playerAmmoText; // текст информации о патронах игрока.

	sf::Vector2f mousePos; // позиция курсора мыши.
	sf::Vector2f playerStartPos; // стартовая позиция игрока.
	sf::Vector2f boxStartPositions[12]; // стартовые позиции коробок.

	sf::Color backgroundColor; // цвет фона.

	sf::Clock clock; // часы.
	sf::Clock fpsClock; // часы для FPS.

	sf::Time fpsPreviousTime; // время предыдущего кадра.
	sf::Time fpsCurrentTime; // время текущего кадра.

	std::string playerName;

	float dt; // время.
	float fps; // кадры в секунду.
	float aimLaserLength; // длина прицельного лазера

	int divisor; // делитель для времени.
	int numberOfEnemies;
	int numberOfPlayers;

	bool showHitbox; // показывать хитбокс?
	bool showAimLaser; // показывать прицельный лазер?
	bool showLogs; // показывать логи?
};


void setColor(GameVariables* gv); // функция установки значений для цвета.

void setFont(GameVariables* gv); // функция установки значений для шрифтов.

void setText(GameVariables* gv); // функция установки значений для текста.

void setImage(GameVariables* gv); // функция установки значений для изображений.

void setTexture(GameVariables* gv); // функция установки значения для текстур.

void setSprite(GameVariables* gv); // функция установки значения для спрайтов.

void setVariables(GameVariables* gv); // общая функция установки значений.