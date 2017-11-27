#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <vector>
using std::vector;

#include "cocos2d.h"
#include "BaseScene.h"
#include "SceneSplashScreen.h"
#include "BattleScene.h"

#define STORAGESIZE 10

/* This is a Class for Scene Management, and it's functions and definitions */
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* getInstance();

	bool Init();

	BaseScene* sceneStorage[STORAGESIZE];

	//These functions are made for the convenience of calling em out instead of writing the entire line
	void Runwithscene(cocos2d::Scene* scene);
	void ReplaceScene(cocos2d::Scene* scene);
	void ReplaceSceneWithTimer(cocos2d::Scene* scene,float timer);
	void SetSceneName(BaseScene* scene, std::string SceneName);
	BaseScene* GetScene(std::string scene);
};

#endif
