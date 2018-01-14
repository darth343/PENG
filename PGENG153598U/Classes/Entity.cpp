#include "Entity.h"

#include "SpriteManager.h"
#include "GridSystem.h"
#include "AnimationManager.h"

Entity::Entity(const std::string& fileName):
	spriteName(fileName)
{
	this->display = Sprite::create();
	SetDisplayFrame(SpriteManager::GetInstance()->GetSpriteFrame(fileName));
	display->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(this->display);
	
	auto collider = PhysicsBody::createCircle((SpriteManager::GetInstance()->GetSpriteWidth(this->spriteName) * 0.5f) * 0.7f);
	collider->setDynamic(false);
	collider->setGravityEnable(false);

	this->addComponent(collider);

	this->RunAnimate(AnimationManager::GetInstance(spriteName)->GetAnimate("IDLE"));
}

Entity::~Entity()
{
}

Entity* Entity::Create(const std::string& fileName)
{
	SpriteFrame* spriteFrame = SpriteManager::GetInstance()->GetSpriteFrame(fileName);
	if (spriteFrame == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return nullptr;
	}

	Entity* entity = new Entity(fileName);
	
	return entity;
}

void Entity::RunAnimate(Action* animate)
{
	this->display->stopAllActions();
	this->display->runAction(animate);
}

void Entity::SetDisplayFrame(SpriteFrame* spriteFrame)
{ 
	if (spriteFrame == nullptr)
		return;

	this->display->setDisplayFrame(spriteFrame);
}