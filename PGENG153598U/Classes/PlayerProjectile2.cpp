#include "PlayerProjectile2.h"

#include "SpriteManager.h"
#include "GameInfo.h"
#include "BattleEntity.h"
#include "NC\ParticleEffectManager\ParticleEffectManager.h"

PlayerProjectile2::PlayerProjectile2(const std::string& fileName) :
	Projectile(fileName)
{
}

PlayerProjectile2::~PlayerProjectile2()
{
}

void PlayerProjectile2::OnCollisionEnter(Entity* other)
{
	BattleEntity* battleEntity = dynamic_cast<BattleEntity*>(other);
	if (battleEntity)
	{
		this->removeFromParentAndCleanup(true);
		battleEntity->TakeDamage(this->damage);
		NC::ParticleEffectManager::getInstance().CreateParticleEffect(1, battleEntity->getPosition(), 0.5f);
	}
}

PlayerProjectile2* PlayerProjectile2::Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly, int damage)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}

	PlayerProjectile2* proj = new PlayerProjectile2(fileName);

	if (isFriendly)
		proj->getPhysicsBody()->setContactTestBitmask(ENEMY_ENTITY);
	else
		proj->getPhysicsBody()->setContactTestBitmask(FRIENDLY_ENTITY);

	proj->getPhysicsBody()->setVelocity(direction.getNormalized() * speed);
	proj->SetDamage(damage);

	return proj;
}