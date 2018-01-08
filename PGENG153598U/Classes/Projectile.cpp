#include "Projectile.h"

#include "SpriteManager.h"
#include "GameInfo.h"
#include "BattleEntity.h"

Projectile::Projectile(const std::string& fileName):
	Entity(fileName)
{
	this->getPhysicsBody()->setCategoryBitmask(PROJECTILE);
	this->getPhysicsBody()->setCollisionBitmask(false);
}

Projectile::~Projectile()
{
}

void Projectile::OnCollisionEnter(Entity* other)
{
	BattleEntity* battleEntity = dynamic_cast<BattleEntity*>(other);
	if (battleEntity)
	{
		this->removeFromParentAndCleanup(true);
	}
}

Projectile* Projectile::Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}

	Projectile* proj = new Projectile(fileName);

	if(isFriendly)
		proj->getPhysicsBody()->setContactTestBitmask(ENEMY_ENTITY);
	else
		proj->getPhysicsBody()->setContactTestBitmask(FRIENDLY_ENTITY);

	proj->getPhysicsBody()->setVelocity(direction.getNormalized() * speed);

	return proj;
}