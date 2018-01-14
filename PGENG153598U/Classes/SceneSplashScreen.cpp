#include "SceneSplashScreen.h"
#include "SimpleAudioEngine.h"
#include "Input.h"

USING_NS_CC;

SceneSplashScreen::SceneSplashScreen()
{

}

SceneSplashScreen::~SceneSplashScreen()
{

}

bool SceneSplashScreen::init()
{
	//Super Init
	if (!Scene::init())
	{
		return false;
	}
	return true;
}

void SceneSplashScreen::update(float dt)
{

}

void SceneSplashScreen::render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection)
{
	Scene::render(renderer, eyeTransform, eyeProjection);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	PostprocTexture->beginWithClear(0, 0, 0, 255);
	RootNode->visit();
	PostprocTexture->end();
}