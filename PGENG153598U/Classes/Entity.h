#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	static Entity* Create(const std::string& fileName);
	Entity(const std::string& fileName);
	virtual ~Entity();

	virtual void OnCollisionEnter(Entity* other) {}
	
	virtual void SetSpriteName(const std::string& _spriteName) { this->spriteName = _spriteName; }
	virtual inline std::string GetSpriteName() { return this->spriteName; }
	virtual void SetDisplayFrame(SpriteFrame* spriteFrame);
	virtual inline Sprite* GetDisplay() { return this->display; }
	virtual inline SpriteFrame* GetDisplayFrame() { return this->display->getDisplayFrame(); }

	virtual void RunAnimate(Action* animate);

protected:
	std::string spriteName;
	Sprite* display = nullptr;
};

#endif
