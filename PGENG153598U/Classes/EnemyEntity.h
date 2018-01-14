#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include "BattleEntity.h"

class EnemyEntity : public BattleEntity
{
public:
	static EnemyEntity* Create(const std::string& fileName, Vec2 gridPos);
	EnemyEntity(const std::string& fileName, Vec2 gridPos);
	~EnemyEntity();

	virtual void Move(Vec2 dir);
	virtual void Attack(Vec2 dir);

private:

	void RunAI();

	float reactionTime;
	float attackCooldown;

	bool canAttackFlag;
	bool actionFinished;
};

#endif