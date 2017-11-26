#ifndef  SCENESSPLASHSCREEN_H_
#define SCENESSPLASHSCREEN_H_
#include "BaseScene.h"
#include "cocos2d.h"

class SceneSplashScreen : public BaseScene
{
protected:
	Input* input;
	Node* RootNode;
	cocos2d::RenderTexture* PostprocTexture;
	float randomtimer = 5.f;
	float timerset;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);


	virtual void update(float delta);
	virtual void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr);

	CREATE_FUNC(SceneSplashScreen);
};


#endif // ! SCENESSPLASHSCREEN_H_
