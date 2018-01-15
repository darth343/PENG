#include "PlayerOverworld.h"
#include "AnimationManager.h"
#include "Input.h"
#include "SpriteManager.h"
#include "BattleScene.h"
#include "OverworldScene.h"
using namespace cocos2d;

//PlayerOverworld::PlayerOverworld() :
//Entity()
//speed(100)
//{
//	
//}

PlayerOverworld::PlayerOverworld(const std::string& spriteName) :
Entity(spriteName),
speed(100),
tip(nullptr),
isInTriggerBox(false)
{
	//SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(spriteName);
	//if (spriteFrame == nullptr)
	//{
	//	cocos2d::log("Entity: %s not found, failed to create entity", spriteName);
	//	return;
	//}

	//this->SetDisplayFrame(spriteFrame);
}

PlayerOverworld::~PlayerOverworld()
{

}

bool PlayerOverworld::init()
{
	if (!Node::init())
	{
		return false;
	}

	keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyPressed = CC_CALLBACK_2(PlayerOverworld::onKeyPressed, this);
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(PlayerOverworld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayerOverworld::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlayerOverworld::onContactSeperate, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool PlayerOverworld::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	//CCLOG("COLLIDED WITH PLAYER");
	Node* player;
	Node* other;

	if (bodyA->getCategoryBitmask() == 2)
	{
		player = bodyA->getNode();
		other = bodyB->getNode();
	}
	else
	{
		other = bodyA->getNode();
		player = bodyB->getNode();
	}

	if (other->getPhysicsBody()->getCategoryBitmask() == 1)
	{
		if (tip == nullptr)
		{
			tip = Label::createWithSystemFont("Press 'N' to go to next scene", "Arial", 50.f);
			tip->setPosition(Director::getInstance()->getVisibleSize() * 0.5f + Size(0, 200));
			tip->setName("Tip");
			player->getParent()->addChild(tip);
		}
		tip->setVisible(true);
		isInTriggerBox = true;
		return false;
	}

	return true;
}

void PlayerOverworld::onContactSeperate(cocos2d::PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	//CCLOG("COLLIDED WITH PLAYER");
	Node* player;
	Node* other;

	if (bodyA->getCategoryBitmask() == 2)
	{
		player = bodyA->getNode();
		other = bodyB->getNode();
	}
	else
	{
		other = bodyA->getNode();
		player = bodyB->getNode();
	}

	if (other->getPhysicsBody()->getCategoryBitmask() == 1)
	{
		isInTriggerBox = false;
		tip->setVisible(false);
	}
}

void PlayerOverworld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			direction += Vec2(0, 1);
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			direction += Vec2(0, -1);
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			direction += Vec2(-1, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			direction += Vec2(1, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_N:
		{
			if (isInTriggerBox)
			{
				auto scene = BattleScene::createScene();
				// Move to next scene
				CCDirector::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
			}
			break;
		}
	}

	this->getPhysicsBody()->setVelocity(direction * speed);
}

void PlayerOverworld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			direction += Vec2(0, -1);
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			direction += Vec2(0, 1);
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			direction += Vec2(1, 0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			direction += Vec2(-1, 0);
			break;
		}
	}
	this->getPhysicsBody()->setVelocity(direction * speed);
}

