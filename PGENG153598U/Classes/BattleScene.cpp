#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "Input.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "PlayerEntity.h"
#include "GridSystem.h"
#include "Grid.h"
#include "PlayerInfo.h"
#include "EnemyEntity.h"
#include "Ghost1.h"
#include "Orc2.h"
#include "GameInfo.h"

USING_NS_CC;

Scene* BattleScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->setName("BattleScene");
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = BattleScene::create();

	layer->setName("Scene");
	layer->retain();

	scene->addChild(layer);

	return scene;
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

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::OnCollisionEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height * 0.6f);

	int numRow = 10;
	int numCol = 5;
	int numPlayerRow = 5;
	int numPlayerCol = 5;

	GridSystem::GetInstance()->GenerateGrid(playingSize, numRow, numCol, numPlayerCol, numPlayerRow);

	RootNode = Node::create();
	RootNode->setName("RootNode");

	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			Sprite* sprite;
			if (i < numPlayerRow && j < numPlayerCol)
				sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
			else
				sprite = Sprite::create("ZigzagForest_Square.png");
			sprite->setContentSize(Size(GridSystem::GetInstance()->GetGridWidth(), GridSystem::GetInstance()->GetGridHeight()));
			sprite->setPosition(GridSystem::GetInstance()->GetGrid(i, j).GetPosition());
			RootNode->addChild(sprite);
		}
	}

	{//Generates sprites for repititve uses
		SpriteManager::GetInstance()->GenerateSprite("sprite2.png", 6, 1);
		SpriteManager::GetInstance()->GenerateSprite("trump_run.png", 6, 4);
		SpriteManager::GetInstance()->GenerateSprite("blinkEffect.png", 10, 1);
		SpriteManager::GetInstance()->GenerateSprite("ZigzagGrass_Mud_Round.png", 1, 1);
		SpriteManager::GetInstance()->GenerateSprite("player.png", 13, 21);
		SpriteManager::GetInstance()->GenerateSprite("orc1.png", 13, 21);
		SpriteManager::GetInstance()->GenerateSprite("orc2.png", 13, 21);
		SpriteManager::GetInstance()->GenerateSprite("ghost1.png", 13, 21);
	}
	{//Setup animations for sprites
		AnimationManager::GetInstance("sprite2.png")->AddAnimate("RUN", 0, 5, 2.0f);

		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_LEFT", 18, 23, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_RIGHT", 6, 11, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_UP", 12, 17, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_DOWN", 0, 5, 0.5f);

		AnimationManager::GetInstance("blinkEffect.png")->AddAnimate("IDLE", 0, 9);

		AnimationManager::GetInstance("player.png")->AddAnimate("IDLE", 143, 151);
		AnimationManager::GetInstance("player.png")->AddAnimate("MOVE", 39, 45, 0.1f);
		AnimationManager::GetInstance("player.png")->AddAnimate("THRUST", 91, 98, PLAYER_ATTACK1_ANIM_SPEED, false);
		AnimationManager::GetInstance("player.png")->AddAnimate("SWING", 195, 200, PLAYER_ATTACK2_ANIM_SPEED, false);
		AnimationManager::GetInstance("player.png")->AddAnimate("DIE", 260, 265, 1.0f, false);

		/*
		Enemy sprite indexes
		IDLE	117 - 125
		THRUST	65 - 72
		WAVE	13 - 19
		DIE		260 - 265
		*/

		AnimationManager::GetInstance("orc1.png")->AddAnimate("IDLE", 117, 125);
		AnimationManager::GetInstance("orc1.png")->AddAnimate("ATTACK", 65, 72, 1.0f, false);
		AnimationManager::GetInstance("orc1.png")->AddAnimate("DIE", 260, 265, 1.0f, false);

		AnimationManager::GetInstance("orc2.png")->AddAnimate("IDLE", 117, 125, 1.5f);
		AnimationManager::GetInstance("orc2.png")->AddAnimate("ATTACK", 65, 72, 1.0f, false);
		AnimationManager::GetInstance("orc2.png")->AddAnimate("DIE", 260, 265, 1.0f, false);

		AnimationManager::GetInstance("ghost1.png")->AddAnimate("IDLE", 117, 125);
		AnimationManager::GetInstance("ghost1.png")->AddAnimate("ATTACK", 13, 19, 1.0f, false);
		AnimationManager::GetInstance("ghost1.png")->AddAnimate("DIE", 260, 265, 1.0f, false);
	}
	{//Creation of entities
		Vec2 halfWorldPos = Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f);

		playerEntity = PlayerEntity::Create("player.png", Vec2(1, 2));
		PlayerInfo::GetInstance()->controllingEntity = playerEntity;
		RootNode->addChild(playerEntity);

		{
			auto enemyEntity = EnemyEntity::Create("orc1.png", Vec2(6, 2));
			RootNode->addChild(enemyEntity);
		}
		{
			auto enemyEntity = EnemyEntity::Create("orc1.png", Vec2(7, 4));
			RootNode->addChild(enemyEntity);
		}
		{
			auto enemyEntity = Ghost1::Create("ghost1.png", Vec2(9, 4));
			RootNode->addChild(enemyEntity);
		}
		{
			auto enemyEntity = Orc2::Create("orc2.png", Vec2(8, 4));
			RootNode->addChild(enemyEntity);
		}
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

bool BattleScene::OnCollisionEvent(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	Entity* entityA = dynamic_cast<Entity*>((bodyA->getNode()));
	Entity* entityB = dynamic_cast<Entity*>((bodyB->getNode()));

	if (entityA != nullptr &&
		entityB != nullptr)
	{
		entityA->OnCollisionEnter(entityB);
		entityB->OnCollisionEnter(entityA);
	}

	return false;
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyPressed(keycode, event);
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		playerEntity->Move(Vec2(0, 1.0f));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		playerEntity->Move(Vec2(0, -1.0f));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		playerEntity->Move(Vec2(-1.0f, 0));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		playerEntity->Move(Vec2(1.0f, 0));
	}

	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_A)
	{
		playerEntity->Fire1(Vec2(1, 0));
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
	{
		playerEntity->Fire2(Vec2(1, 0));
	}
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyReleased(keycode, event);
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
