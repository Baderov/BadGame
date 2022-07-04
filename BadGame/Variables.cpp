#include "Variables.h" // ���������� ������������ ����.

void setColor(GameVariables* gv) // ������� ��������� �������� ��� �����. 
{
	gv->backgroundColor.r = 204; // ������������� ����.
	gv->backgroundColor.g = 153; // ������������� ����.
	gv->backgroundColor.b = 255; // ������������� ����.

	gv->greyColor.r = 120;
	gv->greyColor.g = 120;
	gv->greyColor.b = 120;
}

void setFont(GameVariables* gv) // ������� ��������� �������� ��� �������.
{
	gv->consolasFont.loadFromFile("consolas.ttf"); // ��������� ����� �� ����� � ����������.
}

void setText(GameVariables* gv) // ������� ��������� �������� ��� ������.
{
	gv->gameInfoText.setFont(gv->consolasFont); // ������������� �����.
	gv->gameInfoText.setFillColor(sf::Color::Black); // ������������� ���� ������.

	gv->playerInfoText.setFont(gv->consolasFont); // ������������� �����.
	gv->playerInfoText.setCharacterSize(60);
	gv->playerInfoText.setFillColor(sf::Color::Cyan); // ������������� ���� ������.
	gv->playerInfoText.setOutlineThickness(2.f);

	gv->playerAmmoText.setFont(gv->consolasFont); // ������������� �����.
	gv->playerAmmoText.setCharacterSize(50);
	gv->playerAmmoText.setFillColor(sf::Color::Red); // ������������� ���� ������.
	gv->playerAmmoText.setOutlineThickness(2.f);
}

void setImage(GameVariables* gv) // ������� ��������� �������� ��� �����������.
{
	gv->boxImage.loadFromFile("Images/box.png"); // ��������� ����������� �� ����� � ����������.

	gv->wallImage.loadFromFile("Images/wall.png"); // ��������� ����������� �� ����� � ����������.

	gv->playerImage.loadFromFile("Images/player.png"); // ��������� ����������� �� ����� � ����������.

	gv->enemyImage.loadFromFile("Images/enemy.png"); // ��������� ����������� �� ����� � ����������.

	gv->bulletImage.loadFromFile("Images/bullet.png"); // ��������� ����������� �� ����� � ����������.
	gv->bulletImage.createMaskFromColor(sf::Color(0, 0, 0)); // ������ ����� �� �����.

	gv->goldCoinImage.loadFromFile("Images/goldCoin.png"); // ��������� ����������� �� ����� � ����������.
	gv->goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png"); // ��������� ����������� �� ����� � ����������.

	gv->hpBonusImage.loadFromFile("Images/hpBonus.png"); // ��������� ����������� �� ����� � ����������.

}

void setTexture(GameVariables* gv) // ������� ��������� �������� ��� �������.
{
	gv->goldCoinHUDTexture.loadFromImage(gv->goldCoinHUDImage);
}

void setSprite(GameVariables* gv) // ������� ��������� �������� ��� ��������.
{
	gv->playerDestination.setRadius(20.f); // ������������� ������ �������.
	gv->playerDestination.setOrigin(gv->playerDestination.getRadius(), gv->playerDestination.getRadius()); // ������������� ����� �������.
	gv->playerDestination.setFillColor(sf::Color::Transparent); // ������������� ���� �������.
	gv->playerDestination.setOutlineThickness(5.f); // ������������� ������ ������� �������.
	gv->playerDestination.setOutlineColor(gv->backgroundColor); // ������������� ���� ������� �������.

	gv->goldCoinHUDSprite.setTexture(gv->goldCoinHUDTexture);

	gv->aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	gv->aimLaser.setFillColor(sf::Color::Red);
}

void setVariables(GameVariables* gv) // ����� ������� ��������� ��������.
{
	//gv->window.create(sf::VideoMode(1366, 768), "BadGame", sf::Style::Fullscreen); // ������ ���� � ������������� ����������, ��������� ���� � ����� ����.
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Fullscreen); // ������ ���� � ������������� ����������, ��������� ���� � ����� ����.

	//gv->window.create(sf::VideoMode(1366, 768), "BadGame"); // ������ ���� � ������������� ����������, ��������� ����.
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Close); // ������ ���� � ������������� ����������, ��������� ����.
	//gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Fullscreen); // ������ ���� � ������������� ����������, ��������� ����.

	//gv->window.create(sf::VideoMode(600, 600), "BadGame", sf::Style::Close); // ������ ���� � ������������� ����������, ��������� ����.
	gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Close); // ������ ���� � ������������� ����������, ��������� ����.
	gv->window.setFramerateLimit(75); // ������ ����������� �� ���.

	srand(time(NULL));

	setColor(gv); // ����� ������� ��������� �������� ��� �����. 
	setFont(gv); // ����� ������� ��������� �������� ��� �������.
	setText(gv); // ����� ������� ��������� �������� ��� ������.
	setImage(gv); // ����� ������� ��������� �������� ��� �����������.
	setTexture(gv); // ����� ������� ��������� �������� ��� �������.
	setSprite(gv); // ����� ������� ��������� �������� ��� ��������.

	gv->playerStartPos = sf::Vector2f(1500.f, 1500.f);

	gv->boxStartPositions[0] = sf::Vector2f(250.f, 1100.f);
	gv->boxStartPositions[1] = sf::Vector2f(750.f, 1100.f);
	gv->boxStartPositions[2] = sf::Vector2f(1250.f, 1100.f);
	gv->boxStartPositions[3] = sf::Vector2f(1750.f, 1100.f);
	gv->boxStartPositions[4] = sf::Vector2f(2250.f, 1100.f);
	gv->boxStartPositions[5] = sf::Vector2f(2750.f, 1100.f);

	gv->boxStartPositions[6] = sf::Vector2f(250.f, 1900.f);
	gv->boxStartPositions[7] = sf::Vector2f(750.f, 1900.f);
	gv->boxStartPositions[8] = sf::Vector2f(1250.f, 1900.f);
	gv->boxStartPositions[9] = sf::Vector2f(1750.f, 1900.f);
	gv->boxStartPositions[10] = sf::Vector2f(2250.f, 1900.f);
	gv->boxStartPositions[11] = sf::Vector2f(2750.f, 1900.f);

	// STRING.
	gv->nickname = "";

	// INT.
	gv->divisor = 800; 
	gv->aimLaserLength = 100; 
	gv->numberOfEnemies = 0;
	gv->numberOfPlayers = 0;
	gv->menuNum = 0;
	gv->lineNumberInConsole = 1;

	// BOOL.
	gv->showHitbox = false; 
	gv->showAimLaser = false;
	gv->showLogs = false;
	gv->isGameOver = false; 
	gv->isFullscreen = false; 
	gv->allowButtons = true;
	gv->focusEvent = true;
	gv->multiPlayerGame = false;
	gv->singlePlayerGame = false;

	// CHAR.
	gv->gameLanguage = 'e';

}