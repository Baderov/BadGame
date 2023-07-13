#ifndef BOX_H
#define BOX_H

#include "Entity.h"

class Box : public Entity
{
public:
	explicit Box(std::unique_ptr<GameVariable>& gv);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name);
	void update(std::unique_ptr<GameVariable>& gv) override;
	void move(std::unique_ptr<GameVariable>& gv) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
};

#endif