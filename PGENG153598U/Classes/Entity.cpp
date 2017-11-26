#include "Entity.h"

#include "SpriteManager.h"

Entity::Entity()
{
	this->display = Sprite::create();
	this->addChild(this->display);
}

Entity::~Entity()
{
}

void Entity::Move(Vec2 dir)
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
	Entity* entity = new Entity();
	entity->SetDisplayFrame(spriteFrame);

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