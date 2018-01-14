#include "WaveSpawner.h"

WaveSpawner::WaveSpawner()
{

}

WaveSpawner::~WaveSpawner()
{

}

void WaveSpawner::ActivateWaves()
{
	SetWavenumber(3);
	SetWavetimer(10.f);
	for (int i = 0; i < GetWavenumber(); i++)
	{
		vector<EnemyEntity> Wave_List = vector<EnemyEntity>(3);
		EnemyList.push_back(Wave_List);
	}

	for (int i = 0; i < GetWavenumber(); i++)
	{
		for (int j = 0; j < 2; j++)
		{

		}
	}
}

void WaveSpawner::SpawnEnemies()
{

}

void WaveSpawner::ControlEnemyWave(float delta)
{
	//Checks for collective HP before starting countdown for new Wave

}

float WaveSpawner::getCollectiveHP()
{

}