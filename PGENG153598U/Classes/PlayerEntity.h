#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "Entity.h"

class PlayerEntity : public Entity
{
public:
	static PlayerEntity* Create(const std::string& fileName);
	PlayerEntity();
	virtual ~PlayerEntity();

	virtual void Move(Vec2 dir);

protected:
	float movementDuration;
	float movementCooldown;

	bool canMoveFlag;

};

#endif