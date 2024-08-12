#ifndef ENTITY_H
#define ENTITY_H

#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"

enum class ItemType
{
	GoldCoin, Health
};

enum class WallType
{
	TopWall, BottomWall, LeftWall, RightWall
};

class Entity // common class for all entities.
{
protected:
	float DTMultiplier, maxSpeed, distance, spawnTime, reloadTime, shootTime, shootDelay, shootOffset;
	int HP, maxHP, goldCoins, currentAmmo, maxAmmo, missingAmmo, magazineAmmo;
	bool isAlive, isMove, isShoot, isReload, isCollision, isGhost;
	sf::Clock reloadClock, shootClock;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::CircleShape icon;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape collisionRect, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm, startPos, targetPos;
	std::wstring name, creatorName;
	ItemType itemType;
	WallType wallType;
public:
	explicit Entity(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	virtual void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) = 0;

	void calcTarget(sf::Vector2f moveTargetPos, float&& deltaTime);
	void calcDirection();
	void moveToDirection();
	void updateHPBar();
	void updateLaser(std::unique_ptr<GameVariable>& gv);

	void moveCollisionRect();
	void returnCollisionRect();

	float getShootTime();

	float getSpawnTime();
	float getReloadTime();
	float getShootDelay();
	float getShootOffset();
	int getHP();
	int getMaxHP();
	int getGoldCoins();
	int getCurrentAmmo();
	int getMaxAmmo();
	int getMissingAmmo();
	int getMagazineAmmo();
	bool getIsAlive();
	bool getIsMove();
	bool getIsShoot();
	bool getIsReload();
	bool getIsCollision();
	bool getIsGhost();

	sf::RectangleShape& getCollisionRect();

	sf::Vector2f getSpritePos();
	sf::Vector2f getMoveTargetPos();
	sf::Vector2f getCurrentVelocity();
	sf::Vector2f getStepPos();
	sf::Vector2f getTargetPos();
	sf::Vector2f getAimPos();
	sf::Vector2f getAimDir();
	sf::Vector2f getAimDirNorm();
	std::wstring getName();
	std::wstring getCreatorName();
	ItemType getItemType();
	WallType getWallType();

	void moveSprite(sf::Vector2f& stepPos);
	void setGhostSprite();
	void setRegularSprite();
	void setShootTime(float shootTime);
	void setSpawnTime(float spawnTime);
	void setReloadTime(float reloadTime);
	void setShootDelay(float shootDelay);
	void setShootOffset(float shootOffset);
	void setHP(int HP);
	void setMaxHP(int maxHP);
	void setGoldCoins(int goldCoins);
	void setCurrentAmmo(int currentAmmo);
	void setMaxAmmo(int maxAmmo);
	void setMissingAmmo(int missingAmmo);
	void setMagazineAmmo(int magazineAmmo);
	void setIsAlive(bool isAlive);
	void setIsMove(bool isMove);
	void setIsShoot(bool isShoot);
	void setIsReload(bool isReload);
	void setIsCollision(bool isCollision);
	void setReloadClock(sf::Clock reloadClock);
	void setHpText(sf::Text hpText);
	void setNameText(sf::Text nameText);
	void setReloadText(sf::Text reloadText);
	void setSpritePos(sf::Vector2f spritePos);
	void setMoveTargetPos(sf::Vector2f moveTargetPos);
	void setCurrentVelocity(sf::Vector2f currentVelocity);
	void setStepPos(sf::Vector2f stepPos);
	void setTargetPos(sf::Vector2f targetPos);
	void setAimPos(sf::Vector2f aimPos);
	void setAimDir(sf::Vector2f aimDir);
	void setAimDirNorm(sf::Vector2f aimDirNorm);
	void setName(std::wstring name);
	void setCreatorName(std::wstring creatorName);
	void setIconFillColor(sf::Color color);
	void setIconPosition(sf::Vector2f pos);
	void setIsGhost(bool isGhost);

	void restartReloadClock();
	void restartShootClock();

	void drawIcon(std::unique_ptr<GameWindow>& gw);
	void drawHPText(std::unique_ptr<GameWindow>& gw);
	void drawNameText(std::unique_ptr<GameWindow>& gw);
	void drawReloadText(std::unique_ptr<GameWindow>& gw);
	void drawSprite(std::unique_ptr<GameWindow>& gw);
	void drawCollisionRect(std::unique_ptr<GameWindow>& gw);
	void drawHPBarInner(std::unique_ptr<GameWindow>& gw);
	void drawHPBarOuter(std::unique_ptr<GameWindow>& gw);
	void drawReloadRectInner(std::unique_ptr<GameWindow>& gw);
	void drawReloadRectOuter(std::unique_ptr<GameWindow>& gw);
};

#endif