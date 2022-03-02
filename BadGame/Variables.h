#pragma once // защита от повторного включени€.
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <memory>
#include <cmath>
#include <list>
#include "Button.h"
#include "Label.h"


struct GameVariables // объ€вл€ем структуру дл€ игровых переменных.
{
	sf::RenderWindow window; // главное окно приложени€.

	sf::Event event; // объект событи€.

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

	sf::CircleShape playerDestination; // создаЄм метку передвижени€ игрока.

	sf::View view;

	sf::Font consolasFont; // создаЄм объект шрифта Consolas.
	
	sf::Text gameInfoText; // текст игровой информации.
	sf::Text playerInfoText; // текст информации об игроке.
	sf::Text playerAmmoText; // текст информации о патронах игрока.


	sf::Vector2f mousePos; // позици€ курсора мыши.
	sf::Vector2f playerStartPos; // стартова€ позици€ игрока.
	sf::Vector2f boxStartPositions[12]; // стартовые позиции коробок.

	sf::Color backgroundColor; // цвет фона.
	sf::Color greyColor; // объ€вл€ем серый цвет.

	sf::Clock clock; // часы.
	sf::Clock fpsClock; // часы дл€ FPS.

	sf::Time fpsPreviousTime; // врем€ предыдущего кадра.
	sf::Time fpsCurrentTime; // врем€ текущего кадра.

	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;

	std::string playerName;

	float dt; // врем€.
	float fps; // кадры в секунду.
	float aimLaserLength; // длина прицельного лазера

	int divisor; // делитель дл€ времени.
	int numberOfEnemies;
	int numberOfPlayers;
	int menuNum; // номер меню.
	int lineNumberInConsole; // номер строки в консоли.

	bool showHitbox; // показывать хитбокс?
	bool showAimLaser; // показывать прицельный лазер?
	bool showLogs; // показывать логи?
	bool isGameStarted; // объ€вл€ем логическую переменную.
	bool isGameOver; // объ€вл€ем логическую переменную.
	bool isFullscreen; // объ€вл€ем логическую переменную.

	char gameLanguage;
};

void setColor(GameVariables* gv); // функци€ установки значений дл€ цвета.

void setFont(GameVariables* gv); // функци€ установки значений дл€ шрифтов.

void setText(GameVariables* gv); // функци€ установки значений дл€ текста.

void setImage(GameVariables* gv); // функци€ установки значений дл€ изображений.

void setTexture(GameVariables* gv); // функци€ установки значени€ дл€ текстур.

void setSprite(GameVariables* gv); // функци€ установки значени€ дл€ спрайтов.

void setVariables(GameVariables* gv); // обща€ функци€ установки значений.