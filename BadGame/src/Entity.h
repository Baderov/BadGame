#ifndef ENTITY_H
#define ENTITY_H

#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"
#include "CustomWidget.h"

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
	float DTMultiplier, speed, maxSpeed, distance;
	int HP, maxHP, goldCoins, currentAmmo, maxAmmo, missingAmmo, magazineAmmo, numOfKills, numOfDeaths;
	bool isAlive, isMove, isShoot, isReload, isCollision, isGhost, bulletHit;
	sf::Clock reloadClock, shootClock, menuClock, bulletHitClock;
	sf::Int32 bulletHitTime, shootTime, shootDelay, shootOffset, spawnTime, reloadTime, menuTime;
	sf::Text HPText, nameText, reloadText;
	sf::Color grayColor;
	sf::CircleShape icon;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape collider, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm, startPos, targetPos, moveDir;
	std::wstring name, creatorName;
	ItemType itemType;
	WallType wallType;
public:
	explicit Entity(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	virtual void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw) = 0;
	virtual void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) = 0;
	virtual void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) = 0;

	void calcTarget(sf::Vector2f moveTargetPos, float&& deltaTime);
	void calcStepPos(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm);
	void moveToDirection();

	void updateHP();
	void calculateAmmo();
	void updateReload(std::unique_ptr<GameVariable>& gv);
	void updateReloadRect(std::unique_ptr<GameVariable>& gv);

	void moveCollider();
	void returnCollider();

	void animateBulletHit();
	void restartBulletHitClock();

	sf::Int32 getShootTime();
	sf::Int32 getSpawnTime();
	sf::Int32 getReloadTime();
	sf::Int32 getShootDelay();
	sf::Int32 getShootOffset();
	sf::Int32 getMenuTime();
	sf::Int32 getMenuClockElapsedTime();
	int getHP();
	int getMaxHP();
	int getGoldCoins();
	int getCurrentAmmo();
	int getMaxAmmo();
	int getMissingAmmo();
	int getMagazineAmmo();
	int getNumOfKills();
	int getNumOfDeaths();
	bool getIsAlive();
	bool getIsMove();
	bool getIsShoot();
	bool getIsReload();
	bool getIsCollision();
	bool getIsGhost();
	bool getBulletHit();

	sf::RectangleShape& getCollider();

	sf::Vector2f getSpritePos();
	sf::Vector2f getStartPos();
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
	void setRegularSprite(std::wstring&& currentNickname);
	void setShootTime(sf::Int32 shootTime);
	void setSpawnTime(sf::Int32 spawnTime);
	void setReloadTime(sf::Int32 reloadTime);
	void setShootDelay(sf::Int32 shootDelay);
	void setShootOffset(sf::Int32 shootOffset);
	void setMenuTime(sf::Int32 menuTime);
	void setHP(int HP);
	void setMaxHP(int maxHP);
	void setGoldCoins(int goldCoins);
	void setCurrentAmmo(int currentAmmo);
	void setMaxAmmo(int maxAmmo);
	void setMissingAmmo(int missingAmmo);
	void setMagazineAmmo(int magazineAmmo);
	void setNumOfKills(int numOfKills);
	void setNumOfDeaths(int numOfDeaths);
	void setIsAlive(bool isAlive);
	void setIsMove(bool isMove);
	void setIsShoot(bool isShoot);
	void setIsReload(bool isReload);
	void setIsCollision(bool isCollision);
	void setIsGhost(bool isGhost);
	void setBulletHit(bool bulletHit);
	void setReloadClock(sf::Clock reloadClock);
	void setHpText(sf::Text HPText);
	void setNameText(sf::Text nameText);
	void setReloadText(sf::Text reloadText);
	void setNameTextPos();
	void setSpritePos(sf::Vector2f spritePos);
	void setStartPos(sf::Vector2f startPos);
	void setColliderPos(sf::Vector2f colliderPos);
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
	void setIconPos(sf::Vector2f pos);
	void setNameTextFillColor(sf::Color color);

	void restartReloadClock();
	void restartShootClock();
	void restartMenuClock();

	void drawIcon(std::unique_ptr<GameWindow>& gw);
	void drawNameText(std::unique_ptr<GameWindow>& gw);
	void drawSprite(std::unique_ptr<GameWindow>& gw);
	void drawCollider(std::unique_ptr<GameWindow>& gw);
	void drawHP(std::unique_ptr<GameWindow>& gw);
	void drawReload(std::unique_ptr<GameWindow>& gw);
};

#endif