#pragma once // ������ �� ���������� ���������.
#include "Variables.h" // ���������� ������������ ����.

class Entity // ����� ����� ��� ���� ���������.
{
public:
	Entity(sf::Image& image, sf::Vector2f startPos, std::wstring name);
	virtual void update(GameVariables* gv) = 0; // ������� update ��� ���� �������.
	virtual void move(GameVariables* gv) = 0; // ������� move ��� ���� �������.
	void moveToTarget(sf::Vector2f targetPos, GameVariables* gv);
	void moveToDirection();
	void calcDirection();
	void updateHPBar();

	int& getShootTime();
	int& getShootDelay();
	int& getShootOffset();
	int& getMenuTime();
	int& getHP();
	int& getMaxHP();
	int& getGoldCoins();
	int& getSpawnTime();
	int& getReloadTime();
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


	void setShootTime(int shootTime);
	void setShootDelay(int shootDelay);
	void setShootOffset(int shootOffset);
	void setMenuTime(int menuTime);
	void setHP(int HP);
	void setMaxHP(int maxHP);
	void setGoldCoins(int goldCoins);
	void setSpawnTime(int spawnTime);
	void setReloadTime(int reloadTime);
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
	float maxSpeed, distance;
	int w, h, HP, maxHP, goldCoins, spawnTime, reloadTime, menuTime, shootTime, shootDelay, shootOffset, currentAmmo, maxAmmo, missingAmmo, magazineAmmo; // w - ������ �������, h - ������ �������, HP - ��������, maxHP - ������������ ���������� HP.
	bool isAlive, isMove, isShoot, isReload;
	sf::Clock reloadClock, shootClock;
	sf::Font consolasFont;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::RectangleShape rectHitbox, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm;
	sf::Image image; // ������ �����������.
	sf::Texture texture; // ������ ��������.
	sf::Sprite sprite; // ������ ������.
	std::wstring name, creatorName; // ����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����.
};