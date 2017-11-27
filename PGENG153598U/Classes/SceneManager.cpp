#include "SceneManager.h"

USING_NS_CC;

//Singleton instance
static SceneManager* The_SceneManager = nullptr;

SceneManager::SceneManager()
{
	std::fill(sceneStorage, sceneStorage + STORAGESIZE, nullptr);
}

SceneManager::~SceneManager()
{
	The_SceneManager = nullptr;
}

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
	//Scenes are created inside the Scene Manager, then loaded from AppDelegate
	auto Scene_SplashScreen = SceneSplashScreen::create();
	this->SetSceneName(Scene_SplashScreen, "Splash_Screen");
	auto Scene_Battle = BattleScene::create();
	this->SetSceneName(Scene_Battle, "Battle_Scene");
	sceneStorage[0] = Scene_SplashScreen;
	sceneStorage[1] = Scene_Battle;
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

void SceneManager::SetSceneName(BaseScene* scene, std::string SceneName)
{
	scene->SceneName = SceneName;
}

BaseScene* SceneManager::GetScene(std::string Scene)
{
	for (int i = 0; i < STORAGESIZE; i++)
	{
		if (sceneStorage[i] != nullptr)
		{
			if (sceneStorage[i]->SceneName == Scene)
			{
				return sceneStorage[i];
				break;
			}
		}
		
	}
}