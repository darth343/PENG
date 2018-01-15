#include "Orc2.h"

#include "GridSystem.h"
#include "SpriteManager.h"
#include "PlayerInfo.h"
#include "AnimationManager.h"
#include "Projectile.h"

Orc2::Orc2(const std::string& fileName, Vec2 gridPos) :
	EnemyEntity(fileName, gridPos)
{
	health = 10;
}

Orc2::~Orc2()
{
}

void Orc2::RunAI()
{
	Vec2 playerPos = PlayerInfo::GetInstance()->controllingEntity->GetGridPosition();
	if (canAttackFlag == false)//if attack on cooldown, run from player
	{
		float verticalDirection = cocos2d::clampf(playerPos.y - this->gridPosition.y, -1.0f, 1.0f);
		if (verticalDirection == 0 && canMoveFlag)
		{
			if (cocos2d::random() % 2)
				verticalDirection = 1;
			else
				verticalDirection = -1;

			//out of bound check
			if (this->gridPosition.y + verticalDirection >= GridSystem::GetInstance()->GetNumRow())
				verticalDirection = -1;
			else if (this->gridPosition.y + verticalDirection < 0)
				verticalDirection = 1;

			Move(Vec2(0, verticalDirection));
		}
		else
		{
			Idle(reactionTime);
		}
	}
	else
	{
		if (playerPos.y != this->gridPosition.y && canMoveFlag)
		{//follow player
			Move(Vec2(0, cocos2d::clampf(playerPos.y - this->gridPosition.y, -1.0f, 1.0f)));
		}
		else if (canAttackFlag)
		{//attack
			Attack(playerPos - this->gridPosition);
		}
		else
		{
			Idle(reactionTime);
		}
	}
}

Orc2* Orc2::Create(const std::string& fileName, Vec2 gridPos)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	Orc2* entity = new Orc2(fileName, gridPos);
	entity->SetIsFriendly(false);

	entity->RunAI();

	return entity;
}