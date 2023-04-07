#pragma once // used to provide additional control at compile time.

class Entity // common class for all entities.
{
protected:
	float DTMultiplier, maxSpeed, distance, w, h, spawnTime, reloadTime, menuTime, shootTime, shootDelay, shootOffset;
	int HP, maxHP, goldCoins, currentAmmo, maxAmmo, missingAmmo, magazineAmmo;
	static int numOfEnemies;
	static int numOfClients;
	bool isAlive, isMove, isShoot, isReload;
	sf::Clock reloadClock, shootClock;
	sf::Font consolasFont;
	sf::Text hpText, nameText, reloadText;
	sf::Color grayColor;
	sf::CircleShape icon;
	sf::RectangleShape rectHitbox, HPBarInner, HPBarOuter, reloadRectInner, reloadRectOuter;
	sf::Vector2f moveTargetPos, currentVelocity, stepPos, aimPos, aimDir, aimDirNorm, startPos;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	std::wstring name, creatorName;
	std::string entityType;
	sf::Int32 ping;
	sf::Clock pingClock;
public:
	Entity(sf::Image& image, sf::Vector2f startPos, std::wstring name); // entity constructor.
	Entity(sf::Vector2f startPos, std::wstring name); // entity constructor.
	~Entity();
	virtual void update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer) = 0; // update function for all entities.
	virtual void move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) = 0; // move function for all entities.
	virtual void rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos) = 0; // rotate function.
	void moveToTarget(sf::Vector2f targetPos, float& dt, bool& isSinglePlayer); // a function to move the sprite to the target.
	void moveToDirection(); // function to move the sprite in direction.
	void calcDirection(); // function to calculate direction.
	void updateHPBar(); // function to update HP Bar.
	void updateLaser(sf::Vector2f mousePos, sf::RectangleShape& aimLaser);

	float& getShootTime();
	float& getMenuTime();
	float& getSpawnTime();
	float& getReloadTime();
	float& getShootDelay();
	float& getShootOffset();
	static int& getNumOfClients();
	static int& getNumOfEnemies();
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
	sf::Clock& getPingClock();
	sf::Text& getHPText();
	sf::Text& getNameText();
	sf::Text& getReloadText();
	sf::CircleShape& getIcon();
	sf::RectangleShape& getRectHitbox();
	sf::RectangleShape& getHPBarInner();
	sf::RectangleShape& getHPBarOuter();
	sf::RectangleShape& getReloadRectInner();
	sf::RectangleShape& getReloadRectOuter();
	sf::Vector2f& getMoveTargetPos();
	sf::Vector2f& getCurrentVelocity();
	sf::Vector2f& getStepPos();
	sf::Vector2f& getAimPos();
	sf::Vector2f& getAimDir();
	sf::Vector2f& getAimDirNorm();
	sf::Sprite& getSprite();
	std::wstring& getName();
	std::wstring& getCreatorName();
	std::string& getEntityType();
	sf::Int32 getPing();

	void setPing(sf::Int32 tempPing);
	void setNickPosition();
	void setClientPosition(sf::Vector2f tempStepPos);
	void setShootTime(float shootTime);
	void setMenuTime(float menuTime);
	void setSpawnTime(float spawnTime);
	void setReloadTime(float reloadTime);
	void setShootDelay(float shootDelay);
	void setShootOffset(float shootOffset);
	static void setNumOfClients(int tempNumOfClients);
	static void setNumOfEnemies(int tempNumOfEnemies);
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
	void setCurrentVelocity(sf::Vector2f currentVelocity);
	void setStepPos(sf::Vector2f stepPos);
	void setAimPos(sf::Vector2f aimPos);
	void setAimDir(sf::Vector2f aimDir);
	void setAimDirNorm(sf::Vector2f aimDirNorm);
	void setSprite(sf::Sprite sprite);
	void setName(std::wstring name);
	void setCreatorName(std::wstring creatorName);
	void setEntityType(std::string entityType);
};