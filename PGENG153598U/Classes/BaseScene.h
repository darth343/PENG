#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "Input.h"

class Entity;
class BaseScene : public cocos2d::Scene
{
protected:
	Input* input;
	Node* RootNode;
	cocos2d::RenderTexture* PostprocTexture;

	Entity* test1;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	virtual void update(float delta);
	virtual void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr);

    // implement the "static create()" method manually
	CREATE_FUNC(BaseScene);
};

#endif // __HELLOWORLD_SCENE_H__
