#include "SceneManager.h"

USING_NS_CC;

//Singleton instance
static SceneManager* The_SceneManager = nullptr;

SceneManager::SceneManager()
{
	std::fill(sceneStorage, sceneStorage + STORAGESIZE, nullptr);
	//currentscene = nullptr;
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
	Scene_SplashScreen->retain();
	this->SetSceneName(Scene_SplashScreen, "Splash_Screen");
	auto Scene_Battle = BattleScene::create();
	Scene_Battle->retain();
	this->SetSceneName(Scene_Battle, "Battle_Screen");
	auto Base_Scene = BaseScene::create();
	Base_Scene->retain();
	this->SetSceneName(Base_Scene, "Base_Scene");
	sceneStorage[0] = Scene_SplashScreen;
	sceneStorage[1] = Scene_Battle;
	sceneStorage[2] = Base_Scene;
	return true;
}

void SceneManager::Runwithscene(Scene* scene)
{
	//BaseScene* tempscene = ;
	//currentscene = scene;
	//auto director = cocos2d::Director::getInstance();
	//Scene *temp = director->getRunningScene();

	Scene* current = Director::getInstance()->getRunningScene();
	if (current)
	{
		current->release();
		current->removeFromParentAndCleanup(true);
		current = nullptr;
	}

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