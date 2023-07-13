#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{
public:
	explicit Wall(std::unique_ptr<GameVariable>& gv);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name);
	void update(std::unique_ptr<GameVariable>& gv) override;
	void move(std::unique_ptr<GameVariable>& gv) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
};

#endif