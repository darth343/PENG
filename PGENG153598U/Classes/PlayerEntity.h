#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "BattleEntity.h"

class PlayerEntity : public BattleEntity
{
public:
	static PlayerEntity* Create(const std::string& fileName, Vec2 gridPos);
	PlayerEntity(const std::string& fileName, Vec2 gridPos);
	virtual ~PlayerEntity();

	virtual void Fire1(Vec2 dir);
	virtual void Fire2(Vec2 dir);

protected:

	float attack1_Cooldown;
	float attack2_Cooldown;

	bool canAttack1Flag;
	bool canAttack2Flag;

};

#endif