#ifndef ENTITY_H
#define ENTITY_H

#include "Variables.h"

class Entity // common class for all entities.
{
protected:
	float DTMultiplier, maxSpeed, distance, spawnTime, reloadTime, menuTime, shootTime, shootDelay, shootOffset;
	int HP, maxHP, goldCoins, currentAmmo, maxAmmo, missingAmmo, magazineAmmo;
	bool isAlive, isMove, isShoot, isReload, isCollision;
	sf::Clock reloadClock, shootClock;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::CircleShape icon;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape rectHitbox, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm, startPos, targetPos;
	std::wstring name, creatorName;
public:
	explicit Entity(std::unique_ptr<GameVariable>& gv);
	virtual void update(std::unique_ptr<GameVariable>& gv) = 0; // update function for all entities.
	virtual void move(std::unique_ptr<GameVariable>& gv) = 0; // move function for all entities.
	virtual void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) = 0; // rotate function.

	void moveToTarget(std::unique_ptr<GameVariable>& gv, sf::Vector2f moveTargetPos); // a function to move the sprite to the target.
	void moveToDirection(); // function to move the sprite in direction.
	void calcDirection(); // function to calculate direction.
	void updateHPBar(); // function to update HP Bar.
	void updateLaser(std::unique_ptr<GameVariable>& gv);

	float getShootTime();
	float getMenuTime();
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

	sf::RectangleShape& getRectHitbox();
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

	void setShootTime(float shootTime);
	void setMenuTime(float menuTime);
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
	void setRectHitbox(sf::RectangleShape rectHitbox);
	void setHPBarInner(sf::RectangleShape HPBarInner);
	void setHPBarOuter(sf::RectangleShape HPBarOuter);
	void setReloadRectInner(sf::RectangleShape reloadRectInner);
	void setReloadRectOuter(sf::RectangleShape reloadRectOuter);
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

	void restartReloadClock();
	void restartShootClock();

	void drawIcon(std::unique_ptr<GameVariable>& gv);
	void drawHPText(std::unique_ptr<GameVariable>& gv);
	void drawNameText(std::unique_ptr<GameVariable>& gv);
	void drawReloadText(std::unique_ptr<GameVariable>& gv);
	void drawSprite(std::unique_ptr<GameVariable>& gv);
	void drawRectHitbox(std::unique_ptr<GameVariable>& gv);
	void drawHPBarInner(std::unique_ptr<GameVariable>& gv);
	void drawHPBarOuter(std::unique_ptr<GameVariable>& gv);
	void drawReloadRectInner(std::unique_ptr<GameVariable>& gv);
	void drawReloadRectOuter(std::unique_ptr<GameVariable>& gv);
};
#endif