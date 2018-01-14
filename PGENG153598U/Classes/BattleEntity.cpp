#include "BattleEntity.h"

#include "GridSystem.h"
#include "AnimationManager.h"

BattleEntity::BattleEntity(const std::string& fileName):
	Entity(fileName)
{
	isFriendly = false;

	movementDuration = 0.2f;
	movementCooldown = 0.0f;
}

BattleEntity::~BattleEntity()
{
}

void BattleEntity::TakeDamage(int amount)
{
	this->health -= amount;
	if (health <= 0)
	{
		health = 0;

		Die();
	}
}

void BattleEntity::Die()
{
	this->getPhysicsBody()->removeFromWorld();
	this->stopAllActions();
	this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("DIE"));
	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(1.0f),
		CallFunc::create([&, this]() 
	{
		this->removeFromParentAndCleanup(true); 
	})));
}

void BattleEntity::Move(Vec2 dir)
{
	if (canMoveFlag)
	{
		dir.x = clampf(dir.x, -1, 1);
		dir.y = clampf(dir.y, -1, 1);

		Vec2 nextPos = this->gridPosition + dir;

		if (nextPos.x < 0 || nextPos.x >= GridSystem::GetInstance()->GetNumCol() ||
			nextPos.y < 0 || nextPos.y >= GridSystem::GetInstance()->GetNumRow())
		{
			return;
		}
		if (isFriendly != GridSystem::GetInstance()->GetGrid(nextPos.x, nextPos.y).GetBelongsToPlayer())
		{
			return;
		}

		canMoveFlag = false;
		gridPosition = nextPos;
		dir.x *= GridSystem::GetInstance()->GetGridWidth();
		dir.y *= GridSystem::GetInstance()->GetGridHeight();

		//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("MOVE"));

		Sequence* seq = Sequence::create(
			MoveBy::create(movementDuration, dir),
			DelayTime::create(movementCooldown),
			CallFunc::create([&]()
		{
			canMoveFlag = true;
			//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}), nullptr
		);

		this->runAction(seq);
	}
}