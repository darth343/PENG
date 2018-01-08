#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include "BattleEntity.h"

class EnemyEntity : public BattleEntity
{
public:
	static EnemyEntity* Create(const std::string& fileName);
	EnemyEntity(const std::string& fileName);
	~EnemyEntity();

	Action* Move2(Vec2 dir);
	Action* Attack2(Vec2 dir);

private:

	Action* RunAI();

	float reactionTime;
	float attackCooldown;

	bool canAttackFlag;
};

#endif