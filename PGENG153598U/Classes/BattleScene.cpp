#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "Input.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "PlayerEntity.h"

USING_NS_CC;

Scene* BattleScene::createScene()
{
	return BattleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	//input = Input::create();
	//input->retain();
	//this->addChild(input);
	this->SceneName = "Battle_Scene";

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	RootNode = Node::create();
	RootNode->setName("RootNode");

	Sprite* sprite = Sprite::create("errorTexture.png");
	sprite->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 0.5f));
	sprite->setContentSize(playingSize);
	RootNode->addChild(sprite);

	{//Generates sprites for repititve uses
		SpriteManager::GetInstance()->GenerateSprite("sprite2.png", 6, 1);
		SpriteManager::GetInstance()->GenerateSprite("trump_run.png", 6, 4);
		SpriteManager::GetInstance()->GenerateSprite("blinkEffect.png", 10, 1);
	}
	{//Setup animations for sprites
		AnimationManager::GetInstance("sprite2.png")->AddAnimate("RUN", 0, 5, 2.0f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_LEFT", 18, 23, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_RIGHT", 6, 11, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_UP", 12, 17, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_DOWN", 0, 5, 0.5f);

		AnimationManager::GetInstance("blinkEffect.png")->AddAnimate("DEFAULT", 0, 9, 0.2f);
	}
	{//Creation of entities
		Vec2 halfWorldPos = Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f);

		playerEntity = PlayerEntity::Create("trump_run.png");
		playerEntity->setPosition(halfWorldPos + Vec2(150, 0));
		playerEntity->RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_RIGHT"));
		RootNode->addChild(playerEntity);
	}

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

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

    return true;
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyPressed(keycode, event);
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyReleased(keycode, event);
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		playerEntity->Move(Vec2(0, 50.0f));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		playerEntity->Move(Vec2(0, -50.0f));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		playerEntity->Move(Vec2(-50.0f, 0));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		playerEntity->Move(Vec2(50.0f, 0));
	}
}

void BattleScene::update(float delta)
{
	if (Input::GetKeyDown(EventKeyboard::KeyCode::KEY_W))
	{
		CCLOG("W is Pressed");
	}
	else if (Input::GetKeyUp(EventKeyboard::KeyCode::KEY_W))
	{
		CCLOG("W is Released");
	}
}

void BattleScene::render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection)
{
	Scene::render(renderer, eyeTransform, eyeProjection);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	PostprocTexture->beginWithClear(0, 0, 0, 255);
	RootNode->visit();
	PostprocTexture->end();
}

void BattleScene::menuCloseCallback(Ref* pSender)
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
