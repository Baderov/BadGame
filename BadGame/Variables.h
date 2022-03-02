#pragma once // ������ �� ���������� ���������.
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <memory>
#include <cmath>
#include <list>
#include "Button.h"
#include "Label.h"


struct GameVariables // ��������� ��������� ��� ������� ����������.
{
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

	sf::Time fpsPreviousTime; // ����� ����������� �����.
	sf::Time fpsCurrentTime; // ����� �������� �����.

	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;

	std::string playerName;

	float dt; // �����.
	float fps; // ����� � �������.
	float aimLaserLength; // ����� ����������� ������

	int divisor; // �������� ��� �������.
	int numberOfEnemies;
	int numberOfPlayers;
	int menuNum; // ����� ����.
	int lineNumberInConsole; // ����� ������ � �������.

	bool showHitbox; // ���������� �������?
	bool showAimLaser; // ���������� ���������� �����?
	bool showLogs; // ���������� ����?
	bool isGameStarted; // ��������� ���������� ����������.
	bool isGameOver; // ��������� ���������� ����������.
	bool isFullscreen; // ��������� ���������� ����������.

	char gameLanguage;
};

void setColor(GameVariables* gv); // ������� ��������� �������� ��� �����.

void setFont(GameVariables* gv); // ������� ��������� �������� ��� �������.

void setText(GameVariables* gv); // ������� ��������� �������� ��� ������.

void setImage(GameVariables* gv); // ������� ��������� �������� ��� �����������.

void setTexture(GameVariables* gv); // ������� ��������� �������� ��� �������.

void setSprite(GameVariables* gv); // ������� ��������� �������� ��� ��������.

void setVariables(GameVariables* gv); // ����� ������� ��������� ��������.