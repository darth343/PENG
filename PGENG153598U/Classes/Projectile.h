#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	static Projectile* Create(const std::string& fileName, Vec2 direction, float speed, bool isFriendly);
	Projectile(const std::string& fileName);
	~Projectile();

	virtual void OnCollisionEnter(Entity* other);

private:

};

#endif