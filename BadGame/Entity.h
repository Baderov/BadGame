#pragma once // used to provide additional control at compile time.
#include "Variables.h" // header file for global variables.

class Entity // common class for all entities.
{
public:
	Entity(sf::Image& image, sf::Vector2f startPos, std::wstring name); // entity constructor.
	virtual void update(GameVariable* gv) = 0; // update function for all entities.
	virtual void move(GameVariable* gv) = 0; // move function for all entities.
	void moveToTarget(sf::Vector2f targetPos, GameVariable* gv); // a function to move the sprite to the target.
	void moveToDirection(); // function to move the sprite in direction.
	void calcDirection(); // function to calculate direction.
	void updateHPBar(); // function to update HP Bar.

	float& getShootTime();
	float& getMenuTime();
	float& getSpawnTime();
	float& getReloadTime();
	float& getShootDelay();
	float& getShootOffset();
	int& getHP();
	int& getMaxHP();
	int& getGoldCoins();
	int& getCurrentAmmo();
	int& getMaxAmmo();
	int& getMissingAmmo();
	int& getMagazineAmmo();
	bool& getIsAlive();
	bool& getIsMove();
	bool& getIsShoot();
	bool& getIsReload();
	sf::Clock& getReloadClock();
	sf::Clock& getShootClock();
	sf::Text& getHPText();
	sf::Text& getNameText();
	sf::Text& getReloadText();
	sf::RectangleShape& getRectHitbox();
	sf::RectangleShape& getHPBarInner();
	sf::RectangleShape& getHPBarOuter();
	sf::RectangleShape& getReloadRectInner();
	sf::RectangleShape& getReloadRectOuter();
	sf::Vector2f& getMoveTargetPos();
	sf::Vector2f& getCurrentPos();
	sf::Vector2f& getCurrentVelocity();
	sf::Vector2f& getStepPos();
	sf::Vector2f& getAimPos();
	sf::Vector2f& getAimDir();
	sf::Vector2f& getAimDirNorm();
	sf::Sprite& getSprite();
	std::wstring& getName();
	std::wstring& getCreatorName();

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
	void setReloadClock(sf::Clock reloadClock);
	void setHpText(sf::Text hpText);
	void setNameText(sf::Text nameText);
	void setReloadText(sf::Text reloadText);
	void setRectHitbox(sf::RectangleShape rectHitbox);
	void setHPBarInner(sf::RectangleShape HPBarInner);
	void setHPBarOuter(sf::RectangleShape HPBarOuter);
	void setReloadRectInner(sf::RectangleShape reloadRectInner);
	void setReloadRectOuter(sf::RectangleShape reloadRectOuter);
	void setMoveTargetPos(sf::Vector2f moveTargetPos);
	void setCurrentPos(sf::Vector2f currentPos);
	void setCurrentVelocity(sf::Vector2f currentVelocity);
	void setStepPos(sf::Vector2f stepPos);
	void setAimPos(sf::Vector2f aimPos);
	void setAimDir(sf::Vector2f aimDir);
	void setAimDirNorm(sf::Vector2f aimDirNorm);
	void setSprite(sf::Sprite sprite);
	void setName(std::wstring name);
	void setCreatorName(std::wstring creatorName);

protected:
	float DTMultiplier, maxSpeed, distance, w, h, spawnTime, reloadTime, menuTime, shootTime, shootDelay, shootOffset;
	int HP, maxHP, goldCoins, currentAmmo, maxAmmo, missingAmmo, magazineAmmo;
	bool isAlive, isMove, isShoot, isReload;
	sf::Clock reloadClock, shootClock;
	sf::Font consolasFont;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::RectangleShape rectHitbox, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	std::wstring name, creatorName;
};