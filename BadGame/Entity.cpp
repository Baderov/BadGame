#include "Entity.h" // ���������� ������������ ����.

Entity::Entity(sf::Image& image, sf::Vector2f startPos, std::wstring name)
{
	currentVelocity = sf::Vector2f(0.f, 0.f);
	grayColor.r = 160;
	grayColor.g = 160;
	grayColor.b = 160;
	distance = 0.f;
	maxSpeed = 0.f;
	menuTime = 0;
	currentPos = startPos;
	this->name = name; // ����������� ������ ���������� ������ Entity ��, ��� ������������ ������� � ���������� ��� ������ �������.
	creatorName = L"";
	isAlive = true;
	isShoot = false;

	texture.loadFromImage(image); // ��������� �������� ������� �������� � ��������� ������� ��������.
	sprite.setTexture(texture); // ����� ������������� �������� ��� ��������� �������.
	w = static_cast<float>(texture.getSize().x);
	h = static_cast<float>(texture.getSize().y);
	sprite.setOrigin(w / 2.f, h / 2.f); // ������������� ����������� ����� ��� ���� �������������� (���������, �������, ��������).
	sprite.setPosition(currentPos);

	rectHitbox.setSize(sf::Vector2f(w, h));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
	rectHitbox.setPosition(currentPos);

	HPBarInner.setFillColor(sf::Color::Green);
	HPBarInner.setOutlineThickness(2.f);
	HPBarInner.setOutlineColor(sf::Color::Black);

	HPBarOuter.setFillColor(grayColor);
	HPBarOuter.setOutlineThickness(2.f);
	HPBarOuter.setOutlineColor(sf::Color::Black);

	consolasFont.loadFromFile("consolas.ttf");

	hpText.setFont(consolasFont);
	hpText.setCharacterSize(20);
	hpText.setOutlineThickness(2.f);
	hpText.setString("");

	nameText.setFont(consolasFont);
	nameText.setString("");
	nameText.setFillColor(sf::Color::Cyan);
	nameText.setCharacterSize(25);
	nameText.setOutlineThickness(2.f);
}

void Entity::calcDirection()
{
	aimDir = aimPos - currentPos; // ���������� �� ���� �� ������� ������� ��������.
	aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x) + (aimDir.y * aimDir.y)); // �����������.
	currentVelocity = aimDirNorm * maxSpeed; // ��������� �������� = ����������� * �������� ��������.
}

void Entity::moveToDirection()
{
	sprite.move(currentVelocity);
	currentPos = sprite.getPosition();
}

void Entity::moveToTarget(sf::Vector2f targetPos, GameVariables* gv) // �������� � ������� �������.
{
	// ���������� �� ������� ������� �������� �� ������� �������.
	distance = sqrt(((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x)) + ((targetPos.y - currentPos.y) * (targetPos.y - currentPos.y)));

	// �������, ����� ����� �� �������, ����� ������� �� ����.
	if (distance > 7)
	{
		// stepPos - ������� � ������� �������.
		stepPos.x = currentVelocity.x * static_cast<float>(gv->dt) * (targetPos.x - currentPos.x) / distance;
		stepPos.y = currentVelocity.y * static_cast<float>(gv->dt) * (targetPos.y - currentPos.y) / distance;
		currentPos += stepPos;
	}
	else { isMove = false; } // ����� - �� ���������. 
}

void Entity::updateHPBar()
{
	HPBarOuter.setSize(sf::Vector2f(static_cast<float>(maxHP), 20.f));
	HPBarOuter.setPosition(currentPos.x - 50.f, currentPos.y - 60.f);

	HPBarInner.setSize(sf::Vector2f(static_cast<float>(HP), HPBarOuter.getSize().y));
	HPBarInner.setPosition(HPBarOuter.getPosition().x, HPBarOuter.getPosition().y);

	if (static_cast<float>(HP) <= static_cast<float>(maxHP) / 1.5f)
	{
		HPBarInner.setFillColor(sf::Color::Yellow);
	}
	if (static_cast<float>(HP) <= static_cast<float>(maxHP) / 3.f)
	{
		HPBarInner.setFillColor(sf::Color::Red);
	}
	if (static_cast<float>(HP) > static_cast<float>(maxHP) / 1.5f)
	{
		HPBarInner.setFillColor(sf::Color::Green);
	}
}

sf::Int32& Entity::getMenuTime() { return menuTime; }
sf::Int32& Entity::getShootTime() { return shootTime; }
sf::Int32& Entity::getSpawnTime() { return spawnTime; }
sf::Int32& Entity::getReloadTime() { return reloadTime; }
int& Entity::getHP() { return HP; }
int& Entity::getMaxHP() { return maxHP; }
int& Entity::getGoldCoins() { return goldCoins; }
int& Entity::getCurrentAmmo() { return currentAmmo; }
int& Entity::getMaxAmmo() { return maxAmmo; }
int& Entity::getMissingAmmo() { return missingAmmo; }
int& Entity::getMagazineAmmo() { return magazineAmmo; }
int& Entity::getShootDelay() { return shootDelay; }
int& Entity::getShootOffset() { return shootOffset; }
bool& Entity::getIsAlive() { return isAlive; }
bool& Entity::getIsMove() { return isMove; }
bool& Entity::getIsShoot() { return isShoot; }
bool& Entity::getIsReload() { return isReload; }
sf::Clock& Entity::getReloadClock() { return reloadClock; }
sf::Clock& Entity::getShootClock() { return shootClock; }
sf::Text& Entity::getHPText() { return hpText; }
sf::Text& Entity::getNameText() { return nameText; }
sf::Text& Entity::getReloadText() { return reloadText; }
sf::RectangleShape& Entity::getRectHitbox() { return rectHitbox; }
sf::RectangleShape& Entity::getHPBarInner() { return HPBarInner; }
sf::RectangleShape& Entity::getHPBarOuter() { return HPBarOuter; }
sf::RectangleShape& Entity::getReloadRectInner() { return reloadRectInner; }
sf::RectangleShape& Entity::getReloadRectOuter() { return reloadRectOuter; }
sf::Vector2f& Entity::getMoveTargetPos() { return moveTargetPos; }
sf::Vector2f& Entity::getCurrentPos() { return currentPos; }
sf::Vector2f& Entity::getCurrentVelocity() { return currentVelocity; }
sf::Vector2f& Entity::getStepPos() { return stepPos; }
sf::Vector2f& Entity::getAimPos() { return aimPos; }
sf::Vector2f& Entity::getAimDir() { return aimDir; }
sf::Vector2f& Entity::getAimDirNorm() { return aimDirNorm; }
sf::Sprite& Entity::getSprite() { return sprite; }
std::wstring& Entity::getName() { return name; }
std::wstring& Entity::getCreatorName() { return creatorName; }


void Entity::setMenuTime(sf::Int32 menuTime) { this->menuTime = menuTime; }
void Entity::setSpawnTime(sf::Int32 spawnTime) { this->spawnTime = spawnTime; }
void Entity::setReloadTime(sf::Int32 reloadTime) { this->reloadTime = reloadTime; }
void Entity::setShootTime(sf::Int32 shootTime) { this->shootTime = shootTime; }
void Entity::setHP(int HP) { this->HP = HP; }
void Entity::setMaxHP(int maxHP) { this->maxHP = maxHP; }
void Entity::setShootDelay(int shootDelay) { this->shootDelay = shootDelay; }
void Entity::setShootOffset(int shootOffset) { this->shootOffset = shootOffset; }
void Entity::setGoldCoins(int goldCoins) { this->goldCoins = goldCoins; }
void Entity::setCurrentAmmo(int currentAmmo) { this->currentAmmo = currentAmmo; }
void Entity::setMaxAmmo(int maxAmmo) { this->maxAmmo = maxAmmo; }
void Entity::setMissingAmmo(int missingAmmo) { this->missingAmmo = missingAmmo; }
void Entity::setMagazineAmmo(int magazineAmmo) { this->magazineAmmo = magazineAmmo; }
void Entity::setIsAlive(bool isAlive) { this->isAlive = isAlive; }
void Entity::setIsMove(bool isMove) { this->isMove = isMove; }
void Entity::setIsShoot(bool isShoot) { this->isShoot = isShoot; }
void Entity::setIsReload(bool isReload) { this->isReload = isReload; }
void Entity::setReloadClock(sf::Clock reloadClock) { this->reloadClock = reloadClock; }
void Entity::setHpText(sf::Text hpText) { this->hpText = hpText; }
void Entity::setNameText(sf::Text nameText) { this->nameText = nameText; }
void Entity::setReloadText(sf::Text reloadText) { this->reloadText = reloadText; }
void Entity::setRectHitbox(sf::RectangleShape rectHitbox) { this->rectHitbox = rectHitbox; }
void Entity::setHPBarInner(sf::RectangleShape HPBarInner) { this->HPBarInner = HPBarInner; }
void Entity::setHPBarOuter(sf::RectangleShape HPBarOuter) { this->HPBarOuter = HPBarOuter; }
void Entity::setReloadRectInner(sf::RectangleShape reloadRectInner) { this->reloadRectInner = reloadRectInner; }
void Entity::setReloadRectOuter(sf::RectangleShape reloadRectOuter) { this->reloadRectOuter = reloadRectOuter; }
void Entity::setMoveTargetPos(sf::Vector2f moveTargetPos) { this->moveTargetPos = moveTargetPos; }
void Entity::setCurrentPos(sf::Vector2f currentPos) { this->currentPos = currentPos; }
void Entity::setCurrentVelocity(sf::Vector2f currentVelocity) { this->currentVelocity = currentVelocity; }
void Entity::setStepPos(sf::Vector2f stepPos) { this->stepPos = stepPos; }
void Entity::setAimPos(sf::Vector2f aimPos) { this->aimPos = aimPos; }
void Entity::setAimDir(sf::Vector2f aimDir) { this->aimDir = aimDir; }
void Entity::setAimDirNorm(sf::Vector2f aimDirNorm) { this->aimDirNorm = aimDirNorm; }
void Entity::setSprite(sf::Sprite sprite) { this->sprite = sprite; }
void Entity::setName(std::wstring name) { this->name = name; }
void Entity::setCreatorName(std::wstring creatorName) { this->creatorName = creatorName; }