#include "Projectile.h"

#include "SpriteManager.h"
#include "GameInfo.h"
#include "BattleEntity.h"

Projectile::Projectile(const std::string& fileName):
	Entity(fileName)
{
	auto collider = PhysicsBody::createCircle((SpriteManager::GetInstance()->GetSpriteWidth(this->spriteName) * 0.5f) * 0.7f);
	collider->setDynamic(false);
	collider->setGravityEnable(false);

	this->addComponent(collider);

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
		battleEntity->TakeDamage(this->damage);
	}
}

Projectile* Projectile::Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly, int damage)
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
	proj->SetDamage(damage);

	return proj;
}