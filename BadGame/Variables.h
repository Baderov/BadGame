#pragma once // ������ �� ���������� ���������.
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

struct GameVariables // ��������� ��������� ��� ������� ����������.
{
	MenuErrors menuError;

	sf::RenderWindow window; // ������� ���� ����������.

	sf::Event event; // ������ �������.

	sf::Image playerImage; // �������� ������.
	sf::Image enemyImage; // �������� �����.
	sf::Image wallImage; // �������� �����.
	sf::Image bulletImage; // �������� ����.
	sf::Image boxImage; // �������� �������.
	sf::Image goldCoinImage; // �������� ����.
	sf::Image goldCoinHUDImage; // �������� ����.
	sf::Image hpBonusImage; // �������� �������.

	sf::Texture goldCoinHUDTexture;

	sf::Sprite goldCoinHUDSprite;

	sf::RectangleShape aimLaser; // ���������� �����.

	sf::TcpSocket sock; // ����������� ��������� ��� ����������� ������ ������� ����� ����������.

	sf::CircleShape playerDestination; // ������ ����� ������������ ������.

	sf::View view;

	sf::Font consolasFont; // ������ ������ ������ Consolas.
	
	sf::Text gameInfoText; // ����� ������� ����������.
	sf::Text playerInfoText; // ����� ���������� �� ������.
	sf::Text playerAmmoText; // ����� ���������� � �������� ������.

	sf::Vector2f mousePos; // ������� ������� ����.
	sf::Vector2f playerStartPos; // ��������� ������� ������.
	sf::Vector2f boxStartPositions[12]; // ��������� ������� �������.

	sf::Color backgroundColor; // ���� ����.
	sf::Color greyColor; // ��������� ����� ����.

	sf::Clock clock; // ����.
	sf::Clock fpsClock; // ���� ��� FPS.
	sf::Clock menuClock; // ���� ��� Menu.

	sf::Time fpsPreviousTime; // ����� ����������� �����.
	sf::Time fpsCurrentTime; // ����� �������� �����.

	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;

	std::string nickname;
	std::string serverIP; // ip ����� �������.
	std::string tempPort; // ��������� ���� �������.

	float dt; // �����.
	float fps; // ����� � �������.
	float aimLaserLength; // ����� ����������� ������

	int divisor; // �������� ��� �������.
	int numberOfEnemies;
	int numberOfPlayers;
	int menuNum; // ����� ����.
	int lineNumberInConsole; // ����� ������ � �������.
	int serverPort; // ���� �������.
	int menuTimer;

	bool showHitbox; // ���������� �������?
	bool showAimLaser; // ���������� ���������� �����?
	bool showLogs; // ���������� ����?
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

void setColor(GameVariables* gv); // ������� ��������� �������� ��� �����.

void setFont(GameVariables* gv); // ������� ��������� �������� ��� �������.

void setText(GameVariables* gv); // ������� ��������� �������� ��� ������.

void setImage(GameVariables* gv); // ������� ��������� �������� ��� �����������.

void setTexture(GameVariables* gv); // ������� ��������� �������� ��� �������.

void setSprite(GameVariables* gv); // ������� ��������� �������� ��� ��������.

void setVariables(GameVariables* gv); // ����� ������� ��������� ��������.