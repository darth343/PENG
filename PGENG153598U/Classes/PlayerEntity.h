#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "BattleEntity.h"

class PlayerEntity : public BattleEntity
{
public:
	static PlayerEntity* Create(const std::string& fileName);
	PlayerEntity(const std::string& fileName);
	virtual ~PlayerEntity();

protected:

};

#endif