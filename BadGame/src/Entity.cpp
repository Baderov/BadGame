#include "pch.h"
#include "Entity.h"

Entity::Entity(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	grayColor.r = 160;
	grayColor.g = 160;
	grayColor.b = 160;

	distance = 0.f;
	DTMultiplier = 1000.f;
	speed = 0.f;
	maxSpeed = 0.f;
	spawnTime = 0.f;
	reloadTime = 0.f;
	shootTime = 0.f;
	shootDelay = 1.f;
	shootOffset = 0.f;
	menuTime = 0.f;
	HP = 100;
	maxHP = 100;
	goldCoins = 0;
	currentAmmo = 30;
	maxAmmo = 500;
	missingAmmo = 0;
	magazineAmmo = 30;

	isAlive = false;
	isShoot = false;
	isMove = false;
	isReload = false;
	isCollision = false;
	isGhost = false;
	bulletHit = false;

	currentVelocity = sf::Vector2f(0.f, 0.f);
	moveTargetPos = sf::Vector2f(0.f, 0.f);
	stepPos = sf::Vector2f(0.f, 0.f);
	startPos = sf::Vector2f(0.f, 0.f);
	aimPos = sf::Vector2f(0.f, 0.f);
	aimDir = sf::Vector2f(0.f, 0.f);
	aimDirNorm = sf::Vector2f(0.f, 0.f);
	moveDir = sf::Vector2f(0.f, 0.f);

	creatorName = L"";
	name = L"";

	HPBarInner.setFillColor(sf::Color::Green);
	HPBarInner.setOutlineThickness(2.f);
	HPBarInner.setOutlineColor(sf::Color::Black);

	HPBarOuter.setFillColor(grayColor);
	HPBarOuter.setOutlineThickness(2.f);
	HPBarOuter.setOutlineColor(sf::Color::Black);

	HPText.setFont(gv->consolasFont);
	HPText.setCharacterSize(25);
	HPText.setOutlineThickness(2.f);
	HPText.setString("");

	nameText.setFont(gv->consolasFont);
	nameText.setString("");
	nameText.setFillColor(sf::Color::Cyan);
	nameText.setCharacterSize(25);
	nameText.setOutlineThickness(2.f);

	menuClock.restart();
	shootClock.restart();
	reloadClock.restart();
}

void Entity::calcTarget(sf::Vector2f moveTargetPos, float&& deltaTime)
{
	this->moveTargetPos = std::move(moveTargetPos);

	// distance from the current position of the sprite to the target position.
	distance = sqrt(((this->moveTargetPos.x - sprite.getPosition().x) * (this->moveTargetPos.x - sprite.getPosition().x)) + ((this->moveTargetPos.y - sprite.getPosition().y) * (this->moveTargetPos.y - sprite.getPosition().y)));

	// crutch, so that the player does not twitch when reaching the goal.
	if (distance > 10.f)
	{
		// stepPos - increment to the current position.
		stepPos.x = round((currentVelocity.x * (deltaTime * DTMultiplier) * (this->moveTargetPos.x - sprite.getPosition().x)) / distance);
		stepPos.y = round((currentVelocity.y * (deltaTime * DTMultiplier) * (this->moveTargetPos.y - sprite.getPosition().y)) / distance);
	}
	else { isMove = false; }
}

void Entity::calcStepPos(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm)
{
	isMove = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moveDir.x -= speed;
		isMove = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveDir.x += speed;
		isMove = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveDir.y -= speed;
		isMove = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveDir.y += speed;
		isMove = true;
	}

	if (moveDir.x != 0.f && moveDir.y != 0.f)
	{
		moveDir /= std::sqrt(2.f);
	}

	stepPos = moveDir * gv->getDT();

	moveDir = sf::Vector2f(0.f, 0.f);
}

void Entity::moveToDirection()
{
	sprite.move(currentVelocity);
	collider.move(currentVelocity);
}

void Entity::updateHP()
{
	HPBarOuter.setSize(sf::Vector2f(static_cast<float>(maxHP * 1.5), 30.f));
	HPBarOuter.setPosition(sprite.getPosition().x - 70.f, sprite.getPosition().y - 80.f);

	HPBarInner.setSize(sf::Vector2f(static_cast<float>(HP * 1.5), HPBarOuter.getSize().y));
	HPBarInner.setPosition(HPBarOuter.getPosition().x, HPBarOuter.getPosition().y);

	if (static_cast<float>(HP * 1.5) <= static_cast<float>(maxHP * 1.5) / 1.5f) { HPBarInner.setFillColor(sf::Color::Yellow); }
	if (static_cast<float>(HP * 1.5) <= static_cast<float>(maxHP * 1.5) / 3.f) { HPBarInner.setFillColor(sf::Color::Red); }
	if (static_cast<float>(HP * 1.5) > static_cast<float>(maxHP * 1.5) / 1.5f) { HPBarInner.setFillColor(sf::Color::Green); }

	HPText.setString(std::to_string(HP));
	HPText.setPosition(HPBarOuter.getPosition().x + 3.f, HPBarOuter.getPosition().y - 3.f);
}

void Entity::calculateAmmo()
{
	if (currentAmmo < 30 && isReload && reloadTime >= 2.f)
	{
		missingAmmo = magazineAmmo - currentAmmo;
		if (maxAmmo < magazineAmmo)
		{
			if (maxAmmo + currentAmmo <= 30)
			{
				currentAmmo = currentAmmo + maxAmmo;
				maxAmmo = 0;
			}
			else
			{
				int tempAmmo = magazineAmmo - currentAmmo;
				currentAmmo = currentAmmo + tempAmmo;
				maxAmmo = maxAmmo - tempAmmo;
			}
		}
		else
		{
			currentAmmo = currentAmmo + missingAmmo;
			maxAmmo = maxAmmo - missingAmmo;
		}

		isReload = false;
	}
}

void Entity::updateReload(std::unique_ptr<GameVariable>& gv)
{
	if (isReload)
	{
		reloadTime = reloadClock.getElapsedTime().asSeconds() - menuTime;
		if (reloadTime < 0.f) { reloadTime = 0.f; }
		updateReloadRect(gv);
	}
}

void Entity::updateReloadRect(std::unique_ptr<GameVariable>& gv)
{
	reloadRectOuter.setSize(sf::Vector2f(200.f, 20.f));
	reloadRectOuter.setOrigin(reloadRectOuter.getSize() / 2.f);
	float tempReloadTime = 0.f;
	if (reloadTime > 0.f) { tempReloadTime = (reloadTime * 1000.f) / 10.f; }
	float reloadRectOuterSizeX = reloadRectOuter.getSize().x;
	if (tempReloadTime < reloadRectOuterSizeX) { reloadRectInner.setSize(sf::Vector2f(tempReloadTime, reloadRectOuter.getSize().y)); }
	else { reloadRectInner.setSize(sf::Vector2f(0.f, reloadRectOuter.getSize().y)); }
	reloadRectOuter.setPosition(sprite.getPosition().x, sprite.getPosition().y + 400.f);
	reloadRectInner.setPosition(reloadRectOuter.getPosition().x - (reloadRectOuter.getSize().x / 2.f), reloadRectOuter.getPosition().y - (reloadRectOuter.getSize().y / 2.f));
	if (gv->getGameLanguage() == GameLanguage::English)
	{
		reloadText.setString("RELOAD");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		reloadText.setString(L"œ≈–≈«¿–ﬂƒ ¿");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	reloadText.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y - 50.f);
}

void Entity::moveCollider()
{
	collider.move(stepPos);
}

void Entity::returnCollider()
{
	collider.move(-stepPos);
}

void Entity::animateBulletHit()
{
	if (getBulletHit())
	{
		bulletHitTime = bulletHitClock.getElapsedTime().asMilliseconds();
		if (bulletHitTime < 255)
		{
			sprite.setColor(sf::Color(255, bulletHitTime, bulletHitTime));
		}
		else
		{
			bulletHit = false;
			sprite.setColor(sf::Color::White);
		}
	}
}

void Entity::restartBulletHitClock()
{
	bulletHitClock.restart();
}

float Entity::getShootTime()
{
	float shootTime = this->shootTime;
	return shootTime;
}

float Entity::getSpawnTime()
{
	float spawnTime = this->spawnTime;
	return spawnTime;
}

float Entity::getReloadTime()
{
	float reloadTime = this->reloadTime;
	return reloadTime;
}

float Entity::getShootDelay()
{
	float shootDelay = this->shootDelay;
	return shootDelay;
}

float Entity::getShootOffset()
{
	float shootOffset = this->shootOffset;
	return shootOffset;
}

float Entity::getMenuTime()
{
	float menuTime = this->menuTime;
	return menuTime;
}
float Entity::getMenuClockElapsedTime()
{
	return this->menuClock.getElapsedTime().asSeconds();
}

int Entity::getHP()
{
	int HP = this->HP;
	return HP;
}

int Entity::getMaxHP()
{
	int maxHP = this->maxHP;
	return maxHP;
}

int Entity::getGoldCoins()
{
	int goldCoins = this->goldCoins;
	return goldCoins;
}

int Entity::getCurrentAmmo()
{
	int currentAmmo = this->currentAmmo;
	return currentAmmo;
}

int Entity::getMaxAmmo()
{
	int maxAmmo = this->maxAmmo;
	return maxAmmo;
}

int Entity::getMissingAmmo()
{
	int missingAmmo = this->missingAmmo;
	return missingAmmo;
}

int Entity::getMagazineAmmo()
{
	int magazineAmmo = this->magazineAmmo;
	return magazineAmmo;
}

int Entity::getNumOfKills()
{
	int numOfKills = this->numOfKills;
	return numOfKills;
}

bool Entity::getIsAlive()
{
	bool isAlive = this->isAlive;
	return isAlive;
}

bool Entity::getIsMove()
{
	bool isMove = this->isMove;
	return isMove;
}

bool Entity::getIsShoot()
{
	bool isShoot = this->isShoot;
	return isShoot;
}

bool Entity::getIsReload()
{
	bool isReload = this->isReload;
	return isReload;
}

bool Entity::getIsCollision()
{
	bool isCollision = this->isCollision;
	return isCollision;
}

bool Entity::getIsGhost()
{
	bool isGhost = this->isGhost;
	return isGhost;
}

bool Entity::getBulletHit()
{
	bool bulletHit = this->bulletHit;
	return bulletHit;
}

sf::RectangleShape& Entity::getCollider()
{
	return collider;
}

sf::Vector2f Entity::getSpritePos()
{
	sf::Vector2f spritePos = this->sprite.getPosition();
	return spritePos;
}

sf::Vector2f  Entity::getStartPos()
{
	sf::Vector2f startPos = this->startPos;
	return startPos;
}

sf::Vector2f Entity::getMoveTargetPos()
{
	sf::Vector2f moveTargetPos = this->moveTargetPos;
	return moveTargetPos;
}

sf::Vector2f Entity::getCurrentVelocity()
{
	sf::Vector2f currentVelocity = this->currentVelocity;
	return currentVelocity;
}

sf::Vector2f Entity::getStepPos()
{
	sf::Vector2f stepPos = this->stepPos;
	return stepPos;
}

sf::Vector2f Entity::getTargetPos()
{
	sf::Vector2f targetPos = this->targetPos;
	return targetPos;
}

sf::Vector2f Entity::getAimPos()
{
	sf::Vector2f aimPos = this->aimPos;
	return aimPos;
}

sf::Vector2f Entity::getAimDir()
{
	sf::Vector2f aimDir = this->aimDir;
	return aimDir;
}

sf::Vector2f Entity::getAimDirNorm()
{
	sf::Vector2f aimDirNorm = this->aimDirNorm;
	return aimDirNorm;
}

std::wstring Entity::getName()
{
	std::wstring name = this->name;
	return name;
}

std::wstring Entity::getCreatorName()
{
	std::wstring creatorName = this->creatorName;
	return creatorName;
}

ItemType Entity::getItemType()
{
	ItemType tempItemType = itemType;
	return tempItemType;
}

WallType Entity::getWallType()
{
	WallType tempWallType = wallType;
	return tempWallType;
}

void Entity::moveSprite(sf::Vector2f& stepPos) { sprite.move(stepPos); }
void Entity::setGhostSprite()
{
	sprite.setColor(sf::Color(255, 255, 255, 128));
	nameText.setFillColor(sf::Color(255, 255, 255, 128));
	nameText.setOutlineColor(sf::Color(255, 255, 255, 128));
}
void Entity::setRegularSprite(std::wstring&& currentNickname)
{
	sprite.setColor(sf::Color(255, 255, 255, 255));
	if (name == currentNickname) { nameText.setFillColor(sf::Color::Cyan); }
	else { nameText.setFillColor(sf::Color::Red); }
	nameText.setOutlineColor(sf::Color::Black);
}
void Entity::setSpawnTime(float spawnTime) { this->spawnTime = std::move(spawnTime); }
void Entity::setReloadTime(float reloadTime) { this->reloadTime = std::move(reloadTime); }
void Entity::setShootTime(float shootTime) { this->shootTime = std::move(shootTime); }
void Entity::setShootDelay(float shootDelay) { this->shootDelay = std::move(shootDelay); }
void Entity::setShootOffset(float shootOffset) { this->shootOffset = std::move(shootOffset); }
void Entity::setMenuTime(float menuTime) { this->menuTime = std::move(menuTime); }
void Entity::restartMenuClock() { this->menuClock.restart(); }
void Entity::setHP(int HP) { this->HP = std::move(HP); }
void Entity::setMaxHP(int maxHP) { this->maxHP = std::move(maxHP); }
void Entity::setGoldCoins(int goldCoins) { this->goldCoins = std::move(goldCoins); }
void Entity::setCurrentAmmo(int currentAmmo) { this->currentAmmo = std::move(currentAmmo); }
void Entity::setMaxAmmo(int maxAmmo) { this->maxAmmo = std::move(maxAmmo); }
void Entity::setMissingAmmo(int missingAmmo) { this->missingAmmo = std::move(missingAmmo); }
void Entity::setMagazineAmmo(int magazineAmmo) { this->magazineAmmo = std::move(magazineAmmo); }
void Entity::setNumOfKills(int numOfKills) { this->numOfKills = std::move(numOfKills); }
void Entity::setIsAlive(bool isAlive) { this->isAlive = std::move(isAlive); }
void Entity::setIsMove(bool isMove) { this->isMove = std::move(isMove); }
void Entity::setIsShoot(bool isShoot) { this->isShoot = std::move(isShoot); }
void Entity::setIsReload(bool isReload) { this->isReload = std::move(isReload); }
void Entity::setIsCollision(bool isCollision) { this->isCollision = std::move(isCollision); }
void Entity::setIsGhost(bool isGhost) { this->isGhost = std::move(isGhost); }
void Entity::setBulletHit(bool bulletHit) { this->bulletHit = std::move(bulletHit); }
void Entity::setReloadClock(sf::Clock reloadClock) { this->reloadClock = std::move(reloadClock); }
void Entity::setHpText(sf::Text HPText) { this->HPText = std::move(HPText); }
void Entity::setNameText(sf::Text nameText) { this->nameText = std::move(nameText); }
void Entity::setReloadText(sf::Text reloadText) { this->reloadText = std::move(reloadText); }
void Entity::setNameTextPos() { this->nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 110.f); }
void Entity::setSpritePos(sf::Vector2f spritePos) { this->sprite.setPosition(std::move(spritePos)); }
void Entity::setStartPos(sf::Vector2f startPos) { this->startPos = std::move(startPos); }
void Entity::setColliderPos(sf::Vector2f colliderPos) { this->collider.setPosition(std::move(colliderPos)); }
void Entity::setMoveTargetPos(sf::Vector2f moveTargetPos) { this->moveTargetPos = std::move(moveTargetPos); }
void Entity::setCurrentVelocity(sf::Vector2f currentVelocity) { this->currentVelocity = std::move(currentVelocity); }
void Entity::setStepPos(sf::Vector2f stepPos) { this->stepPos = std::move(stepPos); }
void Entity::setTargetPos(sf::Vector2f targetPos) { this->targetPos = std::move(targetPos); }
void Entity::setAimPos(sf::Vector2f aimPos) { this->aimPos = std::move(aimPos); }
void Entity::setAimDir(sf::Vector2f aimDir) { this->aimDir = std::move(aimDir); }
void Entity::setAimDirNorm(sf::Vector2f aimDirNorm) { this->aimDirNorm = std::move(aimDirNorm); }
void Entity::setName(std::wstring name) { this->name = std::move(name); }
void Entity::setCreatorName(std::wstring creatorName) { this->creatorName = std::move(creatorName); }
void Entity::setIconFillColor(sf::Color color) { this->icon.setFillColor(std::move(color)); }
void Entity::setIconPos(sf::Vector2f pos) { this->icon.setPosition(std::move(pos)); }
void Entity::setNameTextFillColor(sf::Color color) { this->nameText.setFillColor(std::move(color)); }
void Entity::restartReloadClock() { this->reloadClock.restart(); }
void Entity::restartShootClock() { this->shootClock.restart(); }
void Entity::drawIcon(std::unique_ptr<GameWindow>& gw) { gw->window.draw(this->icon); }
void Entity::drawNameText(std::unique_ptr<GameWindow>& gw) { gw->window.draw(this->nameText); }
void Entity::drawSprite(std::unique_ptr<GameWindow>& gw) { gw->window.draw(this->sprite); }
void Entity::drawCollider(std::unique_ptr<GameWindow>& gw) { gw->window.draw(this->collider); }
void Entity::drawHP(std::unique_ptr<GameWindow>& gw) { gw->window.draw(this->HPBarOuter); gw->window.draw(this->HPBarInner); gw->window.draw(this->HPText); }
void Entity::drawReload(std::unique_ptr<GameWindow>& gw)
{
	if (isReload)
	{
		gw->window.draw(this->reloadRectOuter);
		gw->window.draw(this->reloadRectInner);
		gw->window.draw(this->reloadText);
	}
}