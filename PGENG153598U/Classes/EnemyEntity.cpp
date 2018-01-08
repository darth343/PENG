#include "EnemyEntity.h"

#include "SpriteManager.h"
#include "PlayerInfo.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "GameInfo.h"
#include "AnimationManager.h"
#include "GridSystem.h"

EnemyEntity::EnemyEntity(const std::string& fileName):
	BattleEntity(fileName)
{
	reactionTime = 0.2f;
	attackCooldown = 2.0f;
	movementCooldown = 0.2f;
	canAttackFlag = true;

	this->getPhysicsBody()->setCategoryBitmask(ENEMY_ENTITY);
	this->getPhysicsBody()->setCollisionBitmask(false);
	this->getPhysicsBody()->setContactTestBitmask(PROJECTILE);

	auto behavior = RepeatForever::create(Sequence::create(
		DelayTime::create(reactionTime),
		RunAI(), 
		nullptr));

	this->runAction(behavior);
}

EnemyEntity::~EnemyEntity()
{
}

Action* EnemyEntity::RunAI()
{
	Vec2 playerPos = PlayerInfo::GetInstance()->controllingEntity->GetGridPosition();
	if (playerPos.y != this->gridPosition.y)
	{//follow player
		return Move2(Vec2(0, playerPos.y - this->gridPosition.y));
	}
	else
	{//attack
		return Attack2(playerPos - this->gridPosition);
	}
}

Action* EnemyEntity::Move2(Vec2 dir)
{
	if (canMoveFlag)
	{
		dir.x = clampf(dir.x, -1, 1);
		dir.y = clampf(dir.y, -1, 1);

		Vec2 nextPos = this->gridPosition + dir;

		if (nextPos.x < 0 || nextPos.x >= GridSystem::GetInstance()->GetNumCol() ||
			nextPos.y < 0 || nextPos.y >= GridSystem::GetInstance()->GetNumRow())
		{
			return nullptr;
		}
		if (isFriendly != GridSystem::GetInstance()->GetGrid(nextPos.x, nextPos.y).GetBelongsToPlayer())
		{
			return nullptr;
		}

		canMoveFlag = false;
		gridPosition = nextPos;
		dir.x *= GridSystem::GetInstance()->GetGridWidth();
		dir.y *= GridSystem::GetInstance()->GetGridHeight();

		//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("MOVE"));

		Sequence* seq = Sequence::create(
			MoveBy::create(movementDuration, dir),
			CallFunc::create([&]() {}),
			DelayTime::create(movementCooldown),
			CallFunc::create([&]()
		{
			canMoveFlag = true;
			//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}), nullptr
		);

		return seq;
	}
}

Action* EnemyEntity::Attack2(Vec2 dir)
{
	if (canAttackFlag)
	{
		canAttackFlag = false;
		dir.y = 0;
		this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("THRUST"));

		return Sequence::createWithTwoActions(
			DelayTime::create(1.0f),
			CallFunc::create([&, dir]()
		{
			auto proj = Projectile::Create("blinkEffect.png", dir, 200.0f, false);
			this->getParent()->addChild(proj);
			proj->setPosition(this->getPosition());
			this->runAction(Sequence::createWithTwoActions(DelayTime::create(attackCooldown), CallFunc::create([&]() {canAttackFlag = true; })));
			this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}));
	}
}

EnemyEntity* EnemyEntity::Create(const std::string& fileName)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	EnemyEntity* entity = new EnemyEntity(fileName);
	entity->SetIsFriendly(false);

	return entity;
}