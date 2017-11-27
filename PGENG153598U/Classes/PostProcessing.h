#ifndef __POSTPROCESSIN_H__
#define __POSTPROCESSIN_H__

#include "cocos2d.h"
#include "SingletonNodeTemplate.h"
#include <vector>

/*
	PostProcessing Pipeline
*/

struct PostProcShader
{
	PostProcShader(cocos2d::GLProgram* shader, cocos2d::GLProgramState* shaderstate)
	: shaderprog(shader)
	, shaderprogstate(shaderstate)
	{
	}

	cocos2d::GLProgram* shaderprog;
	cocos2d::GLProgramState* shaderprogstate;
};

class PostProcessing : public SingletonNode<PostProcessing>
{
	// Postprocessing Effects
	int textureID = 0;
	cocos2d::RenderTexture** FrameBuffers;
	cocos2d::Texture2D* FinalTexture;

	std::vector<PostProcShader> postprocshaders;

public:
	void SetActive(bool active);
	virtual bool init();
	bool isActive;
	void Render(cocos2d::Node* rootNode);
	void PostProcessing::IncrementTexture();
	cocos2d::Texture2D* GetTexture();
};

#endif