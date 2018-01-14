#ifndef WAVESPAWNER_H_
#define WAVESPAWNER_H_

#include "cocos2d.h"
#include "SingletonTemplate.h"
//#include "EnemyEntity.h"
#include <vector>

using std::vector;
using namespace cocos2d;

class WaveSpawner : public Singleton<WaveSpawner>
{
	friend Singleton<WaveSpawner>;
public:
	virtual ~WaveSpawner();
	WaveSpawner();

	void ActivateWaves();

	void SpawnEnemies();

	void ControlEnemyWave(float delta);

	void SetWavenumber(int newnumber) { this->wavecount = newnumber; }
	int GetWavenumber() { return this->wavecount; }

	void SetWavetimer(float wavetimer) { this->Nextwavetimer = wavetimer; }
	float GetWaveTimer() { return this->Nextwavetimer; }

	float getCollectiveHP();

protected:
	float CollectiveHP;
	int wavecount;
	int Enemiesleft;
	float Nextwavetimer;
	//vector<vector<EnemyEntity>> EnemyList;

};


#endif
