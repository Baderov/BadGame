#ifndef GAME_VARIABLE_H
#define GAME_VARIABLE_H

#include "GameWindow.h"

enum class GameLanguage
{
	English, Russian
};

enum class GameState
{
	GameMenu, MainMenu, StartGame, ContinueGame, GameOver, GameResult, RestartGame
};

class GameVariable
{
private:
	GameLanguage gameLanguage;
	GameState gameState;
	sf::Clock fpsClock;
	sf::Clock gameClock;
	sf::Vector2f mousePos;
	sf::Vector2f targetPos;
	std::mutex mtx;
	std::wstring gameVersion;
	sf::Text gameVersionText;
	float fpsPreviousTime;
	float fpsCurrentTime;
	float fps;
	float dt;
	bool showAimLaser;
	bool showLogs;
	bool showMinimap;
	bool showCollisionRect;
	bool isSingleplayer;
	bool isMultiplayer;
	bool focusEvent;
public:
	sf::Text connectionErrorText;
	sf::Text OKButtonText;
	sf::Text ammoText;
	sf::Font consolasFont;
	sf::RectangleShape connectionErrorRS;
	sf::RectangleShape OKButtonRS;
	sf::RectangleShape aimLaser;
	sf::Image wallImage;
	sf::Image bulletImage;
	sf::Image boxImage;
	sf::Image goldCoinImage;
	sf::Image goldCoinHUDImage;
	sf::Image enemyImage;
	sf::Image playerImage;
	sf::Image hpBonusImage;
	sf::Texture goldCoinHUDTexture;
	sf::Sprite goldCoinHUDSprite;
	sf::Color backgroundColor;
	sf::Color greyColor;

	GameVariable(std::unique_ptr<GameWindow>& gw);
	void resetVariables();

	void updateLaser(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);
	void drawLaser(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw);

	// GETTERS.
	GameLanguage getGameLanguage();
	GameState getGameState();
	sf::Vector2f getMousePos();
	sf::Vector2f getTargetPos();
	std::wstring getGameVersion();
	float getFPS();
	float getDT();
	float getGameClockElapsedTime();
	float getFPSClockElapsedTime();
	float getFPSPreviousTime();
	float getFPSCurrentTime();
	bool getShowAimLaser();
	bool getShowLogs();
	bool getShowMinimap();
	bool getShowCollisionRect();
	bool getIsSingleplayer();
	bool getIsMultiplayer();
	bool getFocusEvent();

	// SETTERS.
	void setGameLanguage(GameLanguage gameLanguage);
	void setGameState(GameState gameState);
	void setMousePos(sf::Vector2f mousePos);
	void setTargetPos(sf::Vector2f targetPos);
	void setGameVersion(std::wstring gameVersion);
	void setFPS(float fps);
	void setFPSPreviousTime(float fpsPreviousTime);
	void setFPSCurrentTime(float fpsCurrentTime);
	void setDT();
	void restartGameClock();
	void setShowAimLaser(bool showAimLaser);
	void setShowLogs(bool showLogs);
	void setShowMinimap(bool showMinimap);
	void setShowCollisionRect(bool showCollisionRect);
	void setIsSingleplayer(bool isSingleplayer);
	void setIsMultiplayer(bool isMultiplayer);
	void setFocusEvent(bool focusEvent);

	void updateGameVersionText(std::unique_ptr<GameWindow>& gw);
	void drawGameVersionText(std::unique_ptr<GameWindow>& gw);
};
#endif