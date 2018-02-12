#include "PlayerEntity.h"

#include "SpriteManager.h"
#include "GameInfo.h"
#include "AnimationManager.h"
#include "Projectile.h"
#include "PlayerProjectile2.h"
#include "GridSystem.h"

PlayerEntity::PlayerEntity(const std::string& fileName, Vec2 gridPos):
BattleEntity(fileName)
{
	this->setPosition(GridSystem::GetInstance()->GetGrid(gridPos.x, gridPos.y).GetPosition());
	this->gridPosition = gridPos;

	movementDuration = PLAYER_MOVE_DURATION;
	movementCooldown = PLAYER_MOVE_COOLDOWN;
	attack1_Cooldown = PLAYER_ATTACK1_COOLDOWN;
	attack2_Cooldown = PLAYER_ATTACK2_COOLDOWN;
	health = PLAYER_HEALTH_AMOUNT;

	this->getPhysicsBody()->setCategoryBitmask(FRIENDLY_ENTITY);
	this->getPhysicsBody()->setCollisionBitmask(false);
	this->getPhysicsBody()->setContactTestBitmask(PROJECTILE);
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Fire1(Vec2 dir)
{
	if (canAttack1Flag)
	{
		canAttack1Flag = false;
		canMoveFlag = false;
		dir.y = 0;
		this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("THRUST"));

		auto seq = Sequence::create(
			DelayTime::create(PLAYER_ATTACK1_ANIM_SPEED),
			CallFunc::create([&, dir]()
		{
			canMoveFlag = true;
			auto proj = Projectile::Create("playerFire1.png", dir, PLAYER_ATTACK1_SPEED, true);
			proj->setScale(0.3f);
			this->getParent()->addChild(proj);
			proj->setPosition(this->getPosition());

			this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}),
			DelayTime::create(attack1_Cooldown),
			CallFunc::create([&]() {canAttack1Flag = true; }),
			nullptr);

		this->runAction(seq);
	}
}
void PlayerEntity::Fire2(Vec2 dir)
{
	if (canAttack2Flag)
	{
		canAttack2Flag = false;
		canMoveFlag = false;
		dir.y = 0;
		this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("SWING"));

		auto seq = Sequence::create(
			DelayTime::create(PLAYER_ATTACK2_ANIM_SPEED),
			CallFunc::create([&, dir]()
		{
			canMoveFlag = true;
			auto proj = PlayerProjectile2::Create("playerFire2.png", dir, PLAYER_ATTACK2_SPEED, true, 3);
			this->getParent()->addChild(proj);
			proj->setPosition(this->getPosition());

			this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
		}),
			DelayTime::create(attack2_Cooldown),
			CallFunc::create([&]() {canAttack2Flag = true; }),
			nullptr);

		this->runAction(seq);
	}
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

PlayerEntity* PlayerEntity::Create(const std::string& fileName, Vec2 gridPos)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}
	PlayerEntity* entity = new PlayerEntity(fileName, gridPos);
	entity->SetIsFriendly(true);
	
	return entity;
}