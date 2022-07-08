#pragma once // защита от повторного включения.
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <SFML/Network.hpp>
#include <memory>
#include <cmath>
#include <list>
#include "Button.h"
#include "Label.h"

enum class MenuErrors
{
	NoErrors, ServerIsNotAvailable, NicknameIsAlreadyTaken, NickMustContainMoreChars
}; 

struct GameVariables // объявляем структуру для игровых переменных.
{
	MenuErrors menuError;


	sf::RenderWindow window; // главное окно приложения.

	sf::Event event; // объект события.

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

	sf::TcpSocket sock; // программный интерфейс для обеспечения обмена данными между процессами.

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
	sf::Color greyColor; // объявляем серый цвет.

	sf::Clock clock; // часы.
	sf::Clock fpsClock; // часы для FPS.

	sf::Time fpsPreviousTime; // время предыдущего кадра.
	sf::Time fpsCurrentTime; // время текущего кадра.

	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;

	std::string nickname;
	std::string serverIP; // ip адрес сервера.
	std::string tempPort; // временный порт сервера.

	float dt; // время.
	float fps; // кадры в секунду.
	float aimLaserLength; // длина прицельного лазера

	int divisor; // делитель для времени.
	int numberOfEnemies;
	int numberOfPlayers;
	int menuNum; // номер меню.
	int lineNumberInConsole; // номер строки в консоли.
	int serverPort; // порт сервера.

	bool showHitbox; // показывать хитбокс?
	bool showAimLaser; // показывать прицельный лазер?
	bool showLogs; // показывать логи?
	bool isGameOver;
	bool isFullscreen; 
	bool allowButtons;
	bool multiPlayerGame;
	bool singlePlayerGame;
	bool focusEvent;
	bool exitFromMenu;
	bool mainMenu;
	bool restartGame;
	bool recvFuncTerminate;

	char gameLanguage;
	char symbol;
	char input;
};

void setColor(GameVariables* gv); // функция установки значений для цвета.

void setFont(GameVariables* gv); // функция установки значений для шрифтов.

void setText(GameVariables* gv); // функция установки значений для текста.

void setImage(GameVariables* gv); // функция установки значений для изображений.

void setTexture(GameVariables* gv); // функция установки значения для текстур.

void setSprite(GameVariables* gv); // функция установки значения для спрайтов.

void setVariables(GameVariables* gv); // общая функция установки значений.