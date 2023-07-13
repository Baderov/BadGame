#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	explicit Player(std::unique_ptr<GameVariable>& gv);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name);
	void update(std::unique_ptr<GameVariable>& gv) override;
	void move(std::unique_ptr<GameVariable>& gv) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
	void updateReloadRect(std::unique_ptr<GameVariable>& gv);
};

#endif