#include "OverworldScene.h"
#include "SimpleAudioEngine.h"
#include "Input.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Entity.h"
#include "PostProcessing.h"
#include "SceneManager.h"
#include "PlayerOverworld.h"
#include "GameInfo.h"

USING_NS_CC;

#define AVERYFAROFFSET cocos2d::Vec2(100000, 100000)
Vec2 distanmceasd;

Scene* OverworldScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->setName("Overworld_Scene");

	auto layer = OverworldScene::create();

	layer->setName("Physics");
	layer->retain();

	scene->addChild(layer);

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void OverworldScene::createMap()
{
	auto WorldMap = Sprite::create("worldMap2.png");
	auto mapCollider1 = PhysicsBody::create();
	//mapCollider1->setCategoryBitmask(2);
	//mapCollider1->setCollisionBitmask(3);
	//mapCollider1->setContactTestBitmask(3);

	WorldMap->addComponent(mapCollider1);
	mapCollider1->setDynamic(false);

	Vec2 collider1[3] = { Vec2(-282, 201), Vec2(-170, -201), Vec2(-282, -201) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider1, 3));

	Vec2 collider2[3] = { Vec2(-212, -69), Vec2(-64, -117), Vec2(-170, -201) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider2, 3));

	Vec2 collider3[3] = { Vec2(-68, -115), Vec2(-8, -125), Vec2(-40, -200) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider3, 3));

	Vec2 collider4[3] = { Vec2(-10, -125), Vec2(58, -101), Vec2(64, -200) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider4, 3));

	Vec2 collider5[3] = { Vec2(56, -102), Vec2(136, -81), Vec2(136, -200) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider5, 3));

	Vec2 collider6[3] = { Vec2(130, -81), Vec2(182, 65), Vec2(264, -61) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider6, 3));

	Vec2 collider7[3] = { Vec2(186, 61), Vec2(264, 91), Vec2(258, 31) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider7, 3));

	Vec2 collider8[3] = { Vec2(-92, 201), Vec2(-76, 55), Vec2(-238, 33) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider8, 3));

	Vec2 collider9[3] = { Vec2(-92, 201), Vec2(18, 40), Vec2(-76, 55) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collider9, 3));

	Vec2 collide10[3] = { Vec2(14, 40), Vec2(46, -18), Vec2(-8, -28) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collide10, 3));

	Vec2 collide11[3] = { Vec2(48, -5), Vec2(144, 169), Vec2(106, 41) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collide11, 3));

	Vec2 collide12[3] = { Vec2(142, 161), Vec2(168, 201), Vec2(280, 186) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collide12, 3));

	Vec2 collide13[3] = { Vec2(270, 187), Vec2(282, 137), Vec2(268, 85) };
	mapCollider1->addShape(PhysicsShapePolygon::create(collide13, 3));

	WorldMap->setPosition(AVERYFAROFFSET);

	this->addChild(WorldMap);
}

// on "init" you need to initialize your instance
bool OverworldScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	glClearColor(0, 255, 0, 255);

	//input = Input::create();
	//input->retain();
	//this->addChild(input);

	UINode = Node::create();
	UINode->setName("UINode");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	RootNode = Node::create();
	RootNode->setName("RootNode");

	auto sprite = Sprite::create("Blue_Front1.png");
	sprite->setPosition(visibleSize * 0.5f);
	sprite->setScale(2.0);

	{//Generates sprites for repititve uses
		SpriteManager::GetInstance()->GenerateSprite("Blue_Front1.png", 1, 1);
		SpriteManager::GetInstance()->GenerateSprite("sprite2.png", 6, 1);
		SpriteManager::GetInstance()->GenerateSprite("trump_run.png", 6, 4);
		SpriteManager::GetInstance()->GenerateSprite("greensquare.png", 1, 1);
	}
	{//Setup animations for sprites
		AnimationManager::GetInstance("sprite2.png")->AddAnimate("RUN", 0, 5, 2.0f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("IDLE", 0, 23, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_RIGHT", 6, 11, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_UP", 12, 17, 0.5f);
		AnimationManager::GetInstance("trump_run.png")->AddAnimate("RUN_DOWN", 0, 5, 0.5f);
	}
	{//Creation of entities
		//test1 = Entity::Create("sprite2.png");
		//test1->setPosition(300, 150);
		//cocos2d::log("entity content size: %f", test1->getContentSize().width);
		//cocos2d::log("entity display size: %f", test1->GetDisplay()->getContentSize().width);
		//cocos2d::log("entity displayFrame rect: %f", test1->GetDisplayFrame()->getRect().size.width);
		//test1->RunAnimate(AnimationManager::GetInstance("sprite2.png")->GetAnimate("RUN"));
		//RootNode->addChild(test1);

		//Vec2 halfWorldPos = Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
		//test1 = Entity::Create("trump_run.png");
		//test1->setPosition(halfWorldPos + Vec2(-150, 0));
		//test1->RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_LEFT"));
		//RootNode->addChild(test1);

		//test1 = Entity::Create("trump_run.png");
		//test1->setPosition(halfWorldPos + Vec2(150, 0));
		//test1->RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_RIGHT"));
		//RootNode->addChild(test1);

		//test1 = Entity::Create("trump_run.png");
		//test1->setPosition(halfWorldPos + Vec2(0, 150));
		//test1->RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_UP"));
		//RootNode->addChild(test1);

		//test1 = Entity::Create("trump_run.png");
		//test1->setPosition(halfWorldPos + Vec2(0, -150));
		//test1->RunAnimate(AnimationManager::GetInstance("trump_run.png")->GetAnimate("RUN_DOWN"));
		//RootNode->addChild(test1);
	}
	
	playerEntity = PlayerOverworld::Create("trump_run.png");
	playerEntity->setName("player");
	playerEntity->setPosition(Vec2(-107, -40) + AVERYFAROFFSET);
	playerEntity->getPhysicsBody()->setCategoryBitmask(2);
	playerEntity->getPhysicsBody()->setContactTestBitmask(1);
	//player->getPhysicsBody()->setCategoryBitmask(1);
	//player->getPhysicsBody()->setCollisionBitmask(3);
	//player->getPhysicsBody()->setContactTestBitmask(3);

	createMap();

	{
		auto triggerbox = Entity::Create("greensquare.png");
		triggerbox->setName("trigger1");
		triggerbox->setPosition(Vec2(94, -80) + AVERYFAROFFSET);
		triggerbox->setScale(0.5, 1);
		triggerbox->setVisible(false);
		auto triggerBoxBody = PhysicsBody::createBox(triggerbox->GetDisplay()->getContentSize(), PhysicsMaterial(0, 0, 0));
		triggerBoxBody->setCategoryBitmask(1);
		triggerBoxBody->setContactTestBitmask(2);
		triggerBoxBody->setPositionOffset(Vec2(0, 40));
		triggerBoxBody->setDynamic(false);
		triggerbox->addComponent(triggerBoxBody);
		this->addChild(triggerbox);
	}

	{
		auto triggerbox = Entity::Create("greensquare.png");
		triggerbox->setName("trigger");
		triggerbox->setPosition(Vec2(217, 90) + AVERYFAROFFSET);
		triggerbox->setScale(0.5, 1);
		triggerbox->setVisible(false);
		auto triggerBoxBody = PhysicsBody::createBox(triggerbox->GetDisplay()->getContentSize(), PhysicsMaterial(0, 0, 0));
		triggerBoxBody->setCategoryBitmask(1);
		triggerBoxBody->setContactTestBitmask(2);
		triggerBoxBody->setPositionOffset(Vec2(0, 40));
		triggerBoxBody->setDynamic(false);
		triggerbox->addComponent(triggerBoxBody);
		this->addChild(triggerbox);
	}
	distanmceasd = Vec2();

	{//Create UI	
	 //auto touchListener = EventListenerTouchOneByOne::create();

	 //touchListener->onTouchBegan = [](Touch* touch, Event* event) {
	 //	//type your code for the callback function here
	 //	return true;
	 //}

	 //_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		Node* virtualJoyNode = Node::create();
		virtualJoyNode->setPositionX(120);
		virtualJoyNode->setPositionY(120);
		UINode->addChild(virtualJoyNode);

		auto button = ui::Button::create();
		button->setTag(BTN_VIRTUALJOY);
		button->setPositionX(0);
		button->setPositionY(0);
		button->loadTextureNormal("virtualJoy_bg.png");
		button->setTouchEnabled(true);
		//upBtn->addTouchEventListener(CC_CALLBACK_2([&, ](this, ui::Widget::TouchEventType::BEGAN) { playerEntity->Move(Vec2(0, 1.0f)); }, this));
		button->addTouchEventListener(CC_CALLBACK_2(OverworldScene::virtualJoyEvent, this));
		virtualJoyNode->addChild(button);

		virtualJoyThumb = Sprite::create("virtualJoy_stick.png");
		virtualJoyThumb->setPositionX(0);
		virtualJoyThumb->setPositionY(0);
		virtualJoyNode->addChild(virtualJoyThumb);

		Node* ABNode = Node::create();
		ABNode->setPositionX(900);
		ABNode->setPositionY(100);
		UINode->addChild(ABNode);

		button = ui::Button::create();
		button->setTag(BTN_A);
		button->setPositionX(50);
		button->setPositionY(20);
		button->loadTextureNormal("A_Button.png");
		button->setTouchEnabled(true);
		//button->addTouchEventListener(CC_CALLBACK_2(BattleScene::onTouchEvent, this));
		ABNode->addChild(button);

		button = ui::Button::create();
		button->setTag(BTN_B);
		button->setPositionX(-50);
		button->setPositionY(-20);
		button->loadTextureNormal("B_Button.png");
		button->setTouchEnabled(true);
		//button->addTouchEventListener(CC_CALLBACK_2(BattleScene::onTouchEvent, this));
		ABNode->addChild(button);
	}

	this->addChild(UINode, 1);

	this->runAction(CCFollow::create(playerEntity));

	this->addChild(playerEntity);

	this->scheduleUpdate();

	return true;
}

void OverworldScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyPressed(keycode, event);
}

void OverworldScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_T)
	{
		auto Scene_Manager = SceneManager::getInstance();
		Scene_Manager->ReplaceScene(Scene_Manager->GetScene("Battle_Screen"));
	}
}

bool OverworldScene::virtualJoyEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	//// get the location of the touch on screen
	//Vec2 location = touch->getLocation();
	//// get the location of the touch relative to your button
	//Vec2 nodeSpaceLocation = playerEntity->getParent()->convertToNodeSpace(location);
	//// check if touch is inside node's bounding box
	//cocos2d:
	//if (playerEntity->getBoundingBox().containsPoint(nodeSpaceLocation)) {
	//	playerEntity->Move(Vec2(0.0f, 1.0f));
	//}
	auto button = dynamic_cast<ui::Button*>(pSender);
	if (!button)
		return false;
	if (button->getTag() != BTN_VIRTUALJOY)
		return false;

	if (eEventType == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		//cocos2d::log("BEGAN");
	}
	else if (eEventType == cocos2d::ui::Widget::TouchEventType::MOVED)
	{
		Vec2 dir = button->getTouchMovePosition() - button->getParent()->getPosition();
		float maxRadius = button->getSize().width * 0.5f;
		if (dir.getLength() > maxRadius)
			dir = dir.getNormalized() * maxRadius;
		virtualJoyThumb->setPositionX(dir.x);
		virtualJoyThumb->setPositionY(dir.y);
		dir.normalize();
		playerEntity->SetVelocityDir(dir);
		//cocos2d::log("MOVE");
	}
	else if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		//cocos2d::log("END");
		virtualJoyThumb->setPositionX(0.0f);
		virtualJoyThumb->setPositionY(0.0f);
		playerEntity->SetVelocityDir(Vec2::ZERO);
	}
	else if (eEventType == cocos2d::ui::Widget::TouchEventType::CANCELED)
	{
		//cocos2d::log("CANCEL");
		virtualJoyThumb->setPositionX(0.0f);
		virtualJoyThumb->setPositionY(0.0f);
		playerEntity->SetVelocityDir(Vec2::ZERO);
	}

	return true;
}

Vec2 realOffset;
void OverworldScene::update(float delta)
{
	if (Input::GetKey(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		distanmceasd += Vec2(1, 0);
	}
	if (Input::GetKey(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		distanmceasd += Vec2(-1, 0);
	}
	if (Input::GetKey(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		distanmceasd += Vec2(0, 1);
	}
	if (Input::GetKey(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		distanmceasd += Vec2(0, -1);
	}

	if (Input::GetKey(EventKeyboard::KeyCode::KEY_O))
	{
		this->getChildByName("player")->getPhysicsBody()->setDynamic(true);
	}

	//this->getChildByName("trigger")->setPosition(this->getChildByName("trigger")->getPosition() + distanmceasd);
	realOffset += distanmceasd;
	distanmceasd = Vec2::ZERO;
	std::string str;
	str += std::to_string(realOffset.x);
	str += " ";
	str += std::to_string(realOffset.y);
	str += " ";
	//CCLOG(str.c_str());
}

void OverworldScene::menuCloseCallback(Ref* pSender)
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
