#include "PlayerEntity.h"

#include "SpriteManager.h"
#include "GameInfo.h"

PlayerEntity::PlayerEntity(const std::string& fileName):
BattleEntity(fileName)
{
	movementDuration = 0.1f;
	movementCooldown = 0.0f;

	this->getPhysicsBody()->setCategoryBitmask(FRIENDLY_ENTITY);
	this->getPhysicsBody()->setCollisionBitmask(false);
	this->getPhysicsBody()->setContactTestBitmask(PROJECTILE);
}

PlayerEntity::~PlayerEntity()
{
}

//void PlayerEntity::Move(Vec2 dir)
//{
//	if (canMoveFlag)
//	{
//		Vec2 nextPos = this->gridPosition + dir;
//
//		if (nextPos.x < 0 || nextPos.x >= GridSystem::GetInstance()->GetNumCol() ||
//			nextPos.y < 0 || nextPos.y >= GridSystem::GetInstance()->GetNumRow())
//		{
//			return;
//		}
//
//		canMoveFlag = false;
//		gridPosition = nextPos;
//		dir.x *= GridSystem::GetInstance()->GetGridWidth();
//		dir.y *= GridSystem::GetInstance()->GetGridHeight();
//
//		RunAnimate(AnimationManager::GetInstance("testSprite.png")->GetAnimate("MOVE"));
//
//		Sequence* seq = Sequence::createWithTwoActions(
//			MoveBy::create(movementDuration, dir),
//			CallFunc::create([&]() 
//		{
//			canMoveFlag = true; 
//			RunAnimate(AnimationManager::GetInstance("testSprite.png")->GetAnimate("IDLE"));
//		})
//		);
//
//		this->runAction(seq);
//	}
//}

PlayerEntity* PlayerEntity::Create(const std::string& fileName)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	PlayerEntity* entity = new PlayerEntity(fileName);
	entity->SetIsFriendly(true);
	
	return entity;
}