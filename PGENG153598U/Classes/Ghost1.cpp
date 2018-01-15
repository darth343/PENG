#include "Ghost1.h"

#include "GridSystem.h"
#include "SpriteManager.h"
#include "PlayerInfo.h"
#include "AnimationManager.h"
#include "Projectile.h"

Ghost1::Ghost1(const std::string& fileName, Vec2 gridPos) :
	EnemyEntity(fileName, gridPos)
{
	reactionTime = 0.5f;
	attackCooldown = 2.0f;
	movementDuration = 1.0f;
	movementCooldown = 0.3f;
	health = 6;
	alternateAction = true;
}

Ghost1::~Ghost1()
{
}

void Ghost1::RunAI()
{
	//if (!actionFinished)
	//	return;

	//actionFinished = false;
	if (alternateAction)
	{
		int halfNumCol = GridSystem::GetInstance()->GetNumCol() * 0.5f;
		
		Vec2 randPoint = Vec2(
			(cocos2d::random() % halfNumCol) + halfNumCol,
			cocos2d::random() % GridSystem::GetInstance()->GetNumRow()
		);
		Move(Vec2(randPoint - this->gridPosition));
		alternateAction = !alternateAction;
	}
	else
	{
		Vec2 playerPos = PlayerInfo::GetInstance()->controllingEntity->GetGridPosition();
		if (playerPos.y != this->gridPosition.y)
		{//follow player
			Move(Vec2(0, playerPos.y - this->gridPosition.y));
		}
		else
		{//attack
			Attack(playerPos - this->gridPosition);
			alternateAction = !alternateAction;
		}
	}
}

Ghost1* Ghost1::Create(const std::string& fileName, Vec2 gridPos)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	Ghost1* entity = new Ghost1(fileName, gridPos);
	entity->SetIsFriendly(false);

	entity->RunAI();

	return entity;
}