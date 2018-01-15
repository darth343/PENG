#ifndef ORC2_H
#define ORC2_H

#include "EnemyEntity.h"

class Orc2 : public EnemyEntity
{
public:
	static Orc2* Create(const std::string& fileName, Vec2 gridPos);
	Orc2(const std::string& fileName, Vec2 gridPos);
	~Orc2();

protected:
	virtual void RunAI();

};

#endif