#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <vector>
#include <utility>
using std::vector;
using std::pair;

#include "cocos2d.h"
#include "BaseScene.h"
#include "SceneSplashScreen.h"
#include "BattleScene.h"

/* This is a Class for Scene Management, and it's functions and definitions */
class SceneManager
{
private:


protected:


public:
	SceneManager() {}
	~SceneManager() {}

	static SceneManager* getInstance();

	bool Init();

	vector <BaseScene* > scenestorage;

	//These functions are made for the convenience of calling em out instead of writing the entire line
	void Runwithscene(cocos2d::Scene* scene);
	void ReplaceScene(cocos2d::Scene* scene);
	void ReplaceSceneWithTimer(cocos2d::Scene* scene,float timer);

	BaseScene* GetScene(std::string scene);
};

#endif
