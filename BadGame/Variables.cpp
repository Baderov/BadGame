#include "Variables.h" // подключаем заголовочный файл.

void setColor(GameVariables* gv) // функция установки значений для цвета. 
{
	gv->backgroundColor.r = 204; // устанавливаем цвет.
	gv->backgroundColor.g = 153; // устанавливаем цвет.
	gv->backgroundColor.b = 255; // устанавливаем цвет.

	gv->greyColor.r = 120;
	gv->greyColor.g = 120;
	gv->greyColor.b = 120;
}

void setFont(GameVariables* gv) // функция установки значений для шрифтов.
{
	gv->consolasFont.loadFromFile("consolas.ttf"); // загружаем шрифт из файла в переменную.
}

void setText(GameVariables* gv) // функция установки значений для текста.
{
	gv->gameInfoText.setFont(gv->consolasFont); // устанавливаем шрифт.
	gv->gameInfoText.setFillColor(sf::Color::Black); // устанавливаем цвет текста.

	gv->playerInfoText.setFont(gv->consolasFont); // устанавливаем шрифт.
	gv->playerInfoText.setCharacterSize(60);
	gv->playerInfoText.setFillColor(sf::Color::Cyan); // устанавливаем цвет текста.
	gv->playerInfoText.setOutlineThickness(2.f);

	gv->playerAmmoText.setFont(gv->consolasFont); // устанавливаем шрифт.
	gv->playerAmmoText.setCharacterSize(50);
	gv->playerAmmoText.setFillColor(sf::Color::Red); // устанавливаем цвет текста.
	gv->playerAmmoText.setOutlineThickness(2.f);
}

void setImage(GameVariables* gv) // функция установки значений для изображений.
{
	gv->boxImage.loadFromFile("Images/box.png"); // загружаем изображение из файла в переменную.

	gv->wallImage.loadFromFile("Images/wall.png"); // загружаем изображение из файла в переменную.

	gv->playerImage.loadFromFile("Images/player.png"); // загружаем изображение из файла в переменную.

	gv->enemyImage.loadFromFile("Images/enemy.png"); // загружаем изображение из файла в переменную.

	gv->bulletImage.loadFromFile("Images/bullet.png"); // загружаем изображение из файла в переменную.
	gv->bulletImage.createMaskFromColor(sf::Color(0, 0, 0)); // создаём маску по цвету.

	gv->goldCoinImage.loadFromFile("Images/goldCoin.png"); // загружаем изображение из файла в переменную.
	gv->goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png"); // загружаем изображение из файла в переменную.

	gv->hpBonusImage.loadFromFile("Images/hpBonus.png"); // загружаем изображение из файла в переменную.

}

void setTexture(GameVariables* gv) // функция установки значения для текстур.
{
	gv->goldCoinHUDTexture.loadFromImage(gv->goldCoinHUDImage);
}

void setSprite(GameVariables* gv) // функция установки значения для спрайтов.
{
	gv->playerDestination.setRadius(20.f); // устанавливаем радиус спрайта.
	gv->playerDestination.setOrigin(gv->playerDestination.getRadius(), gv->playerDestination.getRadius()); // устанавливаем центр спрайта.
	gv->playerDestination.setFillColor(sf::Color::Transparent); // устанавливаем цвет спрайта.
	gv->playerDestination.setOutlineThickness(5.f); // устанавливаем размер контура спрайта.
	gv->playerDestination.setOutlineColor(gv->backgroundColor); // устанавливаем цвет контура спрайта.

	gv->goldCoinHUDSprite.setTexture(gv->goldCoinHUDTexture);

	gv->aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	gv->aimLaser.setFillColor(sf::Color::Red);
}

void setVariables(GameVariables* gv) // общая функция установки значений.
{
	//gv->window.create(sf::VideoMode(1366, 768), "BadGame", sf::Style::Fullscreen); // создаём окно и устанавливаем видеорежим, заголовок окна и стиль окна.
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Fullscreen); // создаём окно и устанавливаем видеорежим, заголовок окна и стиль окна.

	//gv->window.create(sf::VideoMode(1366, 768), "BadGame"); // создаём окно и устанавливаем видеорежим, заголовок окна.
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Close); // создаём окно и устанавливаем видеорежим, заголовок окна.
	//gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Fullscreen); // создаём окно и устанавливаем видеорежим, заголовок окна.

	//gv->window.create(sf::VideoMode(600, 600), "BadGame", sf::Style::Close); // создаём окно и устанавливаем видеорежим, заголовок окна.
	gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Close); // создаём окно и устанавливаем видеорежим, заголовок окна.
	gv->window.setFramerateLimit(75); // ставим ограничение на фпс.

	srand(time(NULL));

	setColor(gv); // вызов функции установки значений для цвета. 
	setFont(gv); // вызов функции установки значений для шрифтов.
	setText(gv); // вызов функции установки значений для текста.
	setImage(gv); // вызов функции установки значений для изображений.
	setTexture(gv); // вызов функции установки значений для текстур.
	setSprite(gv); // вызов функции установки значения для спрайтов.

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