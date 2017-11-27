#include "SceneSplashScreen.h"
#include "SimpleAudioEngine.h"
#include "Input.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "PlayerEntity.h"
#include "SceneManager.h"

USING_NS_CC;

Scene* SceneSplashScreen::createScene()
{
	return SceneSplashScreen::create();
}

bool SceneSplashScreen::init()
{
	//Super Init
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	RootNode = Node::create();
	RootNode->setName("RootNode");

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(SceneSplashScreen::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(SceneSplashScreen::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Set up Post Processin Texture
	PostprocTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	PostprocTexture->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	PostprocTexture->setScale(1.f);
	PostprocTexture->clear(0, 0, 0, 255);

	this->addChild(PostprocTexture);

	this->addChild(RootNode);
	RootNode->retain();
	this->scheduleUpdate();

	this->SceneName = "Splash_Screen";
	return true;
}

void SceneSplashScreen::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyPressed(keycode, event);
}

void SceneSplashScreen::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyReleased(keycode, event);
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
	{
		auto Scene_Manager = SceneManager::getInstance();
		Scene_Manager->ReplaceScene(Scene_Manager->GetScene("Battle_Screen"));
	}
}

void SceneSplashScreen::update(float dt)
{
	timerset += dt;
	if (timerset > randomtimer)
	{
		auto Scene_Manager = SceneManager::getInstance();
		Scene_Manager->ReplaceScene(Scene_Manager->GetScene("Battle_Screen"));
	}
		
}

void SceneSplashScreen::render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection)
{
	Scene::render(renderer, eyeTransform, eyeProjection);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	PostprocTexture->beginWithClear(0, 0, 0, 255);
	RootNode->visit();
	PostprocTexture->end();
}

void SceneSplashScreen::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application, do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}