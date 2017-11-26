#include "SceneManager.h"

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
	if (!SceneManager::Init())
	{
		return false;
	}

	//Scenes are created inside the Scene Manager, then loaded from AppDelegate
	auto Scene_SplashScreen = SceneSplashScreen::create();
	scenestorage.push_back(Scene_SplashScreen);

	return true;
}

void SceneManager::Runwithscene(cocos2d::Scene* scene)
{
	cocos2d::Director::getInstance()->runWithScene(scene);
}

void SceneManager::ReplaceScene(cocos2d::Scene* scene)
{
	cocos2d::Director::getInstance()->replaceScene(scene);
}

BaseScene* SceneManager::GetScene(std::string Scene)
{
	for (int i = 0; i < sizeof(scenestorage); i++)
	{
		if (scenestorage[i]->SceneName == Scene)
		{
			return scenestorage[i];
		}
	}
}