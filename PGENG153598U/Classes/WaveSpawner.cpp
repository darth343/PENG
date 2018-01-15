#include "WaveSpawner.h"
#include "GridSystem.h"

#include "Ghost1.h"
#include "Orc2.h"

WaveSpawner::WaveSpawner()
{

}

WaveSpawner::~WaveSpawner()
{

}

void WaveSpawner::ActivateWaves()
{
	SetWavenumber(3);
	SetWavetimer(5.0f);
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
	//int halfNumCol = GridSystem::GetInstance()->GetNumCol() * 0.5f;

	for (int j = 0; j < 3; j++)
	{
		//Vec2 randPoint = Vec2(
		//	(cocos2d::random() % halfNumCol) + halfNumCol,
		//	cocos2d::random() % GridSystem::GetInstance()->GetNumRow()
		//);
		int halfNumCol = GridSystem::GetInstance()->GetNumCol() * 0.5f;
		Vec2 randPoint = Vec2(
			(cocos2d::random() % halfNumCol) + halfNumCol,
			cocos2d::random() % GridSystem::GetInstance()->GetNumRow()
		);
		switch (cocos2d::random() % 3)
		{

		case 0:
			EnemyList[GetWavenumber() - 1][j] = EnemyEntity::Create("orc1.png", randPoint);
			break;
		case 1:
			EnemyList[GetWavenumber() - 1][j] = Orc2::Create("orc2.png", randPoint);
			break;
		case 2:
			EnemyList[GetWavenumber() - 1][j] = Ghost1::Create("ghost1.png", randPoint);
			break;
		}
		//EnemyList[GetWavenumber()-1][j]->SetGridPosition(Vec2(6, RandomHelper::random_int(0, 4)));
		node->addChild(EnemyList[GetWavenumber()-1][j]);
	}
	
}

void WaveSpawner::ControlEnemyWave(float delta, Node* node)
{
	//Checks for collective HP before starting countdown for new Wave
	cocos2d::log("%d", (getCollectiveHP()));
	if (getCollectiveHP() <= 0)
	{
		Nextwavetimer -= delta;
	}
	if (Nextwavetimer <= 0 && GetWavenumber() > 0)
	{
		int temp = GetWavenumber();
		temp -= 1;
		SetWavenumber(temp);
		if (wavecount == 0)
		{
			CCDirector::getInstance()->popScene();
		}
		else
		{
			SpawnEnemies(node);
		}
		
		SetWavetimer(5.0f);
	}
}

float WaveSpawner::getCollectiveHP()
{
	int HPpercentage = 0.f;
	for (int i = 0; i < 3; i++)
	{
		HPpercentage += EnemyList[GetWavenumber()-1][i]->GetHealth();
	}
	return HPpercentage;
}