#ifndef  SCENESSPLASHSCREEN_H_
#define SCENESSPLASHSCREEN_H_
#include "BaseScene.h"
#include "cocos2d.h"

class SceneSplashScreen : public BaseScene
{
public:
	SceneSplashScreen();
	~SceneSplashScreen();

	std::string SceneName = "Splash_Screen";

	virtual bool init();

	virtual void update(float delta);
	virtual void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr);

};


#endif // ! SCENESSPLASHSCREEN_H_
