#include "PlayerEntity.h"

#include "SpriteManager.h"
#include "AnimationManager.h"
#include "GridSystem.h"

PlayerEntity::PlayerEntity():
Entity()
{
	movementDuration = 0.2f;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Move(Vec2 dir)
{
	if (canMoveFlag)
	{
		canMoveFlag = false;
		dir.x *= GridSystem::GetInstance()->GetGridWidth();
		dir.y *= GridSystem::GetInstance()->GetGridHeight();

		RunAnimate(AnimationManager::GetInstance("testSprite.png")->GetAnimate("MOVE"));

		Sequence* seq = Sequence::createWithTwoActions(
			MoveBy::create(movementDuration, dir),
			CallFunc::create([&]() 
		{
			canMoveFlag = true; 
			RunAnimate(AnimationManager::GetInstance("testSprite.png")->GetAnimate("IDLE"));
		})
		);

		this->runAction(seq);
	}
}

PlayerEntity* PlayerEntity::Create(const std::string& fileName)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	PlayerEntity* entity = new PlayerEntity();
	entity->SetDisplayFrame(spriteFrame);

	return entity;
}