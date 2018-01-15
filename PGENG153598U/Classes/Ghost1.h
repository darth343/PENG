#ifndef GHOST1_H
#define GHOST1_H

#include "EnemyEntity.h"

class Ghost1 : public EnemyEntity
{
public:
	static Ghost1* Create(const std::string& fileName, Vec2 gridPos);
	Ghost1(const std::string& fileName, Vec2 gridPos);
	~Ghost1();

protected:
	virtual void RunAI();

	bool alternateAction;

};



#endif