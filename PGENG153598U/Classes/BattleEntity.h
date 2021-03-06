#ifndef BATTLEENTITY_H
#define BATTLEENTITY_H

#include "Entity.h"

class BattleEntity : public Entity
{
public:
	BattleEntity(const std::string& fileName);
	~BattleEntity();

	virtual void Move(Vec2 dir);
	virtual void Attack(Vec2 dir){}
	virtual void Die();

	virtual void TakeDamage(int amount);
	virtual inline int GetHealth() { return this->health; }

	virtual inline void SetGridPosition(Vec2 pos) { this->gridPosition = pos; }
	virtual inline Vec2 GetGridPosition() { return this->gridPosition; }

	virtual inline void SetIsFriendly(bool _flag) { this->isFriendly = _flag; }
	virtual inline bool GetIsFriendly() { return this->isFriendly; }

protected:
	Vec2 gridPosition;

	int health;

	float movementDuration;
	float movementCooldown;

	bool canMoveFlag;

	bool isFriendly;

};

#endif