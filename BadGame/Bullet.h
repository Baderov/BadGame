#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
private:
	bool allowToShoot;
public:
	explicit Bullet(std::unique_ptr<GameVariable>& gv);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, sf::Vector2f aimPos, std::wstring name, std::wstring creatorName);
	void update(std::unique_ptr<GameVariable>& gv) override;
	void move(std::unique_ptr<GameVariable>& gv) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;

	bool getAllowToShoot();
	void setAllowToShoot(bool allowToShoot);
};

#endif