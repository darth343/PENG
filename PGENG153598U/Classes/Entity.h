#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	Entity();
	virtual ~Entity();
	static Entity* Create(const std::string& fileName);

	virtual void SetDisplayFrame(SpriteFrame* spriteFrame);
	virtual inline Sprite* GetDisplay() { return this->display; }
	virtual inline SpriteFrame* GetDisplayFrame() { return this->display->getDisplayFrame(); }

	void RunAnimate(Action* animate);

protected:
	Sprite* display = nullptr;
};

#endif
