#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "SingletonTemplate.h"

class BattleEntity;
class PlayerInfo : public Singleton<PlayerInfo>
{
	friend Singleton<PlayerInfo>;
public:
	virtual ~PlayerInfo();

	BattleEntity* controllingEntity;

protected:

private:
	PlayerInfo();
};

#endif
