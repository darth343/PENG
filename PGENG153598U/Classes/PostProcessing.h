#ifndef __POSTPROCESSIN_H__
#define __POSTPROCESSIN_H__

#include "cocos2d.h"

/*
	PostProcessing Pipeline
*/

class PostProcessing
{
	// Postprocessing Effects
	cocos2d::Sprite currentFrame;

public:
	void Render(cocos2d::Node rootNode);
	cocos2d::Texture2D* GetTexture();
};

#endif