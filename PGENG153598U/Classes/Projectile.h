#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	static Projectile* Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly, int damage = 1);
	Projectile(const std::string& fileName);
	~Projectile();

	virtual void OnCollisionEnter(Entity* other);

	virtual inline void SetDamage(int amount) { this->damage = amount; }

protected:

	int damage;

};

#endif