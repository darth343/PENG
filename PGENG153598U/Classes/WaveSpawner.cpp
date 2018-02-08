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
		vector<EnemyEntity*> Wave_List = vector<EnemyEntity*>(3);
		for (int j = 0; j < Wave_List.size(); j++)
		{
			//Wave_List[j] = EnemyEntity::Create("orc1.png", Vec2(0, 0));
		}
		EnemyList.push_back(Wave_List);
	}
}

void WaveSpawner::SpawnEnemies(Node* node)
{
	for (int j = 0; j < 3; j++)
	{
		EnemyList[GetWavenumber() - 1][j] = EnemyEntity::Create("orc1.png", Vec2(6, RandomHelper::random_int(0, 4)));
		//EnemyList[GetWavenumber()-1][j]->SetGridPosition(Vec2(6, RandomHelper::random_int(0, 4)));
		EnemyList[GetWavenumber()-1][j]->GetDisplay()->setScale(2);
		node->addChild(EnemyList[GetWavenumber()-1][j]);
	}
	
}

void WaveSpawner::ControlEnemyWave(float delta, Node* node)
{
	//Checks for collective HP before starting countdown for new Wave
	if (getCollectiveHP() <= 0)
	{
		Nextwavetimer -= delta;
	}
	if (Nextwavetimer <= 0 && GetWavenumber() >= 0)
	{
		int temp = GetWavenumber();
		temp -= 1;
		SetWavenumber(temp);
		SpawnEnemies(node);
		SetWavetimer(10.f);
	}
}

float WaveSpawner::getCollectiveHP()
{
	float HPpercentage = 0.f;
	for (int i = 0; i < 3; i++)
	{
		HPpercentage += EnemyList[GetWavenumber()-1][i]->getHealth();
	}
	return HPpercentage;
}