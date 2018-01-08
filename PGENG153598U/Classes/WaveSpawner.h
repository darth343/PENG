#ifndef WAVESPAWNER_H_
#define WAVESPAWNER_H_

#include "cocos2d.h"
#include "SingletonTemplate.h"

using namespace cocos2d;

class WaveSpawner : public Singleton<WaveSpawner>
{
	friend Singleton<WaveSpawner>;
public:
	virtual ~WaveSpawner();
	WaveSpawner();

	void SpawnEnemies();

	void ControlEnemyWave();

	void SetWavenumber(int newnumber) { this->wavenumber = newnumber; }
	int GetWavenumber() { return this->wavenumber; }

protected:
	float CollectiveHP;
	int wavenumber;
	int Enemiesleft;


};


#endif
