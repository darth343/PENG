#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	static Entity* Create(const std::string& fileName);
	Entity();
	virtual ~Entity();
	
	virtual void SetDisplayFrame(SpriteFrame* spriteFrame);
	virtual inline Sprite* GetDisplay() { return this->display; }
	virtual inline SpriteFrame* GetDisplayFrame() { return this->display->getDisplayFrame(); }

	virtual void RunAnimate(Action* animate);

	virtual void Move(Vec2 dir);

protected:
	Sprite* display = nullptr;
};

#endif
