#include "SceneManager.h"

USING_NS_CC;

//Singleton instance
static SceneManager* The_SceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
	if (!The_SceneManager)
	{
		The_SceneManager = new (std::nothrow) SceneManager;
		The_SceneManager->Init();
	}

	return The_SceneManager;
}

bool SceneManager::Init()
{
	/*if (!SceneManager::Init())
	{
		return false;
	}*/

	//Scenes are created inside the Scene Manager, then loaded from AppDelegate
	//auto Scene_SplashScreen = SceneSplashScreen::create();
	//scenestorage.push_back(Scene_SplashScreen);
	//auto Scene_Battle = BattleScene::create();
	//scenestorage.push_back(Scene_Battle);

	return true;
}

void SceneManager::Runwithscene(Scene* scene)
{
	Director::getInstance()->runWithScene(scene);
}

void SceneManager::ReplaceScene(Scene* scene)
{
	Director::getInstance()->replaceScene(scene);
}

void SceneManager::ReplaceSceneWithTimer(Scene* scene, float timer)
{
	TransitionFade::create(timer, scene, Color3B(0, 255, 255));
}

BaseScene* SceneManager::GetScene(std::string Scene)
{
	for (int i = 0; i < scenestorage.size(); i++)
	{
		if (scenestorage[i]->SceneName == Scene)
		{
			return scenestorage[i];
		}
	}

	//return scenestorage[0];
	/*for (std::vector<BaseScene*>::iterator it = scenestorage.begin(); it != scenestorage.end(); it++)
	{
		if ((*it)->SceneName == Scene)
		{
			return *it;
		}
	}*/
}