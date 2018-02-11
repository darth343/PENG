#ifndef __OVERWORLD_SCENE_H__
#define __OVERWORLD_SCENE_H__

#include "cocos2d.h"
#include "Input.h"
#include "BaseScene.h"
#include "ui\UIButton.h"

using namespace cocos2d;

class PlayerEntity;
class OverworldScene : public BaseScene
{
protected:
	Node* RootNode;
	Node* UINode;
	Node* virtualJoyThumb;
	cocos2d::Sprite* ScreenSprite;

	PlayerEntity* playerEntity;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//virtual void SetupControls();

	void createMap();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	bool virtualJoyEvent(Ref* pSender, ui::Widget::TouchEventType eEventType);

	virtual void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(OverworldScene);
};

#endif // __BATTLE_SCENE_H__
