#ifndef PLAYERPROJECTILE2_H
#define PLAYERPROJECTILE2_H

#include "Entity.h"
#include "Projectile.h"

class PlayerProjectile2 : public Projectile
{
public:
	static PlayerProjectile2* Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly, int damage = 1);
	PlayerProjectile2(const std::string& fileName);
	virtual ~PlayerProjectile2();

	virtual void OnCollisionEnter(Entity* other);

protected:
};

#endif