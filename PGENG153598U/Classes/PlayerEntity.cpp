#include "PlayerEntity.h"

#include "SpriteManager.h"
#include "AnimationManager.h"

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

		RunAnimate(AnimationManager::GetInstance("blinkEffect.png")->GetAnimate("DEFAULT"));

		Sequence* seq = Sequence::createWithTwoActions(
			MoveBy::create(movementDuration, dir),
			CallFunc::create([&]() 
		{
			canMoveFlag = true; 
			RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_RIGHT"));
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