#pragma once
#include "cocos2d.h"
#include "Entity.h"
using cocos2d::Sprite;
class PlayerOverworld : public Entity
{
private:
	float speed;
	bool isInTriggerBox;
	cocos2d::Vec2 direction;
	cocos2d::EventListenerKeyboard* keyboardlistener;
	cocos2d::EventListenerPhysicsContact* contactListener;
	cocos2d::Node* tip;

public:
	static PlayerOverworld* Create(std::string name)
	{
		PlayerOverworld* player = new PlayerOverworld(name);
		if (!player->init())
			return NULL;
		auto physicsBody = PhysicsBody::createBox(Size(40, 70), PhysicsMaterial(0, 0, 1));
		physicsBody->setPositionOffset(Vec2(0, 45));
		physicsBody->setDynamic(true);
		physicsBody->setRotationEnable(false);
		physicsBody->setGravityEnable(false);
		player->setPhysicsBody(physicsBody);
		return player;
	}

	virtual bool init();
	//virtual void update(float delta);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactSeperate(cocos2d::PhysicsContact &contact);

	void SetVelocityDir(Vec2 dir);

	//PlayerOverworld();
	PlayerOverworld(const std::string& spriteName);
	~PlayerOverworld();
};