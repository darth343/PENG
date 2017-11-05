#include "BaseScene.h"
#include "SimpleAudioEngine.h"
#include "Input.h"

USING_NS_CC;

Scene* BaseScene::createScene()
{
	return BaseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BaseScene::init()
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

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	RootNode = Node::create();
	RootNode->setName("RootNode");

	auto sprite = Sprite::create("Blue_Front1.png");
	sprite->setPosition(visibleSize * 0.5f);
	sprite->setScale(2.0);

	RootNode->addChild(sprite);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// Set up Post Processin Texture
	PostprocTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	PostprocTexture->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	PostprocTexture->setScale(1.f);
	PostprocTexture->clear(0, 0, 0, 255);

	this->addChild(PostprocTexture);

	//this->addChild(RootNode);
	RootNode->retain();
	this->scheduleUpdate();

    return true;
}

void BaseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyPressed(keycode, event);
}

void BaseScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//input->onKeyReleased(keycode, event);
}

void BaseScene::update(float delta)
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

void BaseScene::render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection)
{
	Scene::render(renderer, eyeTransform, eyeProjection);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	PostprocTexture->beginWithClear(0, 0, 0, 255);
	RootNode->visit();
	PostprocTexture->end();
}

void BaseScene::menuCloseCallback(Ref* pSender)
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
