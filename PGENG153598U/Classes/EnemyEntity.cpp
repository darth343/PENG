#include "EnemyEntity.h"

#include "SpriteManager.h"
#include "PlayerInfo.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "GameInfo.h"
#include "AnimationManager.h"
#include "GridSystem.h"

EnemyEntity::EnemyEntity(const std::string& fileName, Vec2 gridPos):
	BattleEntity(fileName)
{
	reactionTime = 0.2f;
	attackCooldown = 2.0f;
	movementDuration = 0.2f;
	movementCooldown = 0.2f;
	health = 5;
	canAttackFlag = true;
	canMoveFlag = true;
	isFriendly = false;
	actionFinished = true;

	this->setPosition(GridSystem::GetInstance()->GetGrid(gridPos.x, gridPos.y).GetPosition());
	this->gridPosition = gridPos;

	this->getPhysicsBody()->setCategoryBitmask(ENEMY_ENTITY);
	this->getPhysicsBody()->setCollisionBitmask(false);
	this->getPhysicsBody()->setContactTestBitmask(PROJECTILE);

	this->RunAI();
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::RunAI()
{
	//if (!actionFinished)
	//	return;

	//actionFinished = false;
	Vec2 playerPos = PlayerInfo::GetInstance()->controllingEntity->GetGridPosition();
	if (playerPos.y != this->gridPosition.y)
	{//follow player
		Move(Vec2(0, cocos2d::clampf(playerPos.y - this->gridPosition.y, -1.0f, 1.0f)));
	}
	else
	{//attack
		Attack(playerPos - this->gridPosition);
	}
}

void EnemyEntity::Move(Vec2 dir)
{
	if (canMoveFlag)
	{
		//canMoveFlag = false;
		//dir.x = (int)(dir.x + 0.5f);
		//dir.y = (int)(dir.y + 0.5f);

		Vec2 nextGridPos = this->gridPosition + dir;

		if (isFriendly != GridSystem::GetInstance()->GetGrid(nextGridPos.x, nextGridPos.y).GetBelongsToPlayer())
		{
			//return nullptr;
			dir.x = 0.0f;
			dir.y = 0.0f;
		}//do another check if occupied
		else if (GridSystem::GetInstance()->GetGrid(nextGridPos.x, nextGridPos.y).GetIsOccupied())
		{
			dir.x = 0.0f;
			dir.y = 0.0f;
		}
		else
		{
			if (nextGridPos.x < 0 || nextGridPos.x >= GridSystem::GetInstance()->GetNumCol())
			{
				dir.x = 0.0f;
			}
			if (nextGridPos.y < 0 || nextGridPos.y >= GridSystem::GetInstance()->GetNumRow())
			{
				dir.y = 0.0f;
			}
		}

		nextGridPos = this->gridPosition + dir;
		GridSystem::GetInstance()->GetGrid(gridPosition.x, gridPosition.y).SetIsOccupied(false);
		this->gridPosition = nextGridPos;
		GridSystem::GetInstance()->GetGrid(gridPosition.x, gridPosition.y).SetIsOccupied(true);
		dir.x *= GridSystem::GetInstance()->GetGridWidth();
		dir.y *= GridSystem::GetInstance()->GetGridHeight();

		//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("MOVE"));

		Sequence* seq = Sequence::create(
			MoveBy::create(movementDuration, dir),
			DelayTime::create(movementCooldown),
			CallFunc::create([&]()
		{
			canMoveFlag = true;
			actionFinished = true;
			//RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}),
			DelayTime::create(reactionTime), 
			CallFunc::create([&]() {RunAI(); }),
			nullptr
		);

		this->runAction(seq);
	}
	else
	{
		this->RunAI();
	}
}

void EnemyEntity::Attack(Vec2 dir)
{
	if (canAttackFlag)
	{
		//canAttackFlag = false;
		dir.y = 0;
		this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("THRUST"));

		auto seq = Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create([&, dir]()
		{
			auto proj = Projectile::Create("blinkEffect.png", dir, 200.0f, false);
			this->getParent()->addChild(proj);
			proj->setPosition(this->getPosition());

			this->runAction(Sequence::createWithTwoActions(
				DelayTime::create(attackCooldown), 
				CallFunc::create([&]() 
			{
				canAttackFlag = true; 
			})));
			actionFinished = true;
			this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}),
			DelayTime::create(reactionTime),
			CallFunc::create([&]() {RunAI(); }),
			nullptr);

		this->runAction(seq);
	}
	else
	{
		this->RunAI();
	}
}

EnemyEntity* EnemyEntity::Create(const std::string& fileName, Vec2 gridPos)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	EnemyEntity* entity = new EnemyEntity(fileName, gridPos);
	entity->SetIsFriendly(false);

	return entity;
}