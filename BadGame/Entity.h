#pragma once // защита от повторного включения.
#include "Variables.h" // подключаем заголовочный файл.

class Entity // общий класс для всех сущностей.
{
public:
	Entity(sf::Image& image, sf::Vector2f startPos, std::wstring name);
	virtual void update(GameVariables* gv) = 0; // функция update для всех существ.
	virtual void move(GameVariables* gv) = 0; // функция move для всех существ.
	void moveToTarget(sf::Vector2f targetPos, GameVariables* gv);
	void moveToDirection();
	void calcDirection();
	void updateHPBar();

	sf::Int32& getShootTime();
	sf::Int32& getMenuTime();
	sf::Int32& getSpawnTime();
	sf::Int32& getReloadTime();
	int& getShootDelay();
	int& getShootOffset();
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

	void setShootTime(sf::Int32 shootTime);
	void setMenuTime(sf::Int32 menuTime);
	void setSpawnTime(sf::Int32 spawnTime);
	void setReloadTime(sf::Int32 reloadTime);
	void setShootDelay(int shootDelay);
	void setShootOffset(int shootOffset);
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
	sf::Int32 spawnTime, reloadTime, menuTime, shootTime;
	float maxSpeed, distance, w, h;
	int HP, maxHP, goldCoins, shootDelay, shootOffset, currentAmmo, maxAmmo, missingAmmo, magazineAmmo; // w - ширина спрайта, h - высота спрайта, HP - здоровье, maxHP - максимальное количество HP.
	bool isAlive, isMove, isShoot, isReload;
	sf::Clock reloadClock, shootClock;
	sf::Font consolasFont;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::RectangleShape rectHitbox, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm;
	sf::Image image; // создаём изображение.
	sf::Texture texture; // создаём текстуру.
	sf::Sprite sprite; // создаём спрайт.
	std::wstring name, creatorName; // враги могут быть разные, мы не будем делать другой класс для врага.Всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени.
};