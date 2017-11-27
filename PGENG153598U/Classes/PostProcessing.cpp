#include "PostProcessing.h"
#include "Input.h"
using namespace cocos2d;

bool PostProcessing::init()
{
	if (!Node::init())
	{
		return false;
	}

	GLProgram* brightpass = new GLProgram();
	brightpass->initWithFilenames("shaders/BasicVertex.vsh", "shaders/BrightPass.fsh");
	brightpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	brightpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	brightpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	brightpass->link();
	brightpass->updateUniforms();
	brightpass->retain();

	GLProgram* horiblurpass = new GLProgram();
	horiblurpass->initWithFilenames("shaders/BasicVertex.vsh", "shaders/HoriBlurPass.fsh");
	horiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	horiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	horiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	horiblurpass->link();
	horiblurpass->updateUniforms();
	horiblurpass->retain();


	GLProgram* vertiblurpass = new GLProgram();
	vertiblurpass->initWithFilenames("shaders/BasicVertex.vsh", "shaders/VertiBlurPass.fsh");
	vertiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	vertiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	vertiblurpass->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	vertiblurpass->link();
	vertiblurpass->updateUniforms();
	vertiblurpass->retain();

	GLProgram* combinefilter = new GLProgram();
	combinefilter->initWithFilenames("shaders/BasicVertex.vsh", "shaders/CombineFilter.fsh");
	combinefilter->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	combinefilter->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	combinefilter->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	combinefilter->link();
	combinefilter->updateUniforms();
	combinefilter->retain();

	GLProgramState* brightpassState = GLProgramState::create(brightpass);
	brightpassState->setUniformFloat("brightcheckvalue", 0.3f);
	brightpassState->retain();

	GLProgramState* horiblurState = GLProgramState::create(horiblurpass);
	horiblurState->setUniformInt("steps", 2);
	horiblurState->retain();

	GLProgramState* vertiblurState = GLProgramState::create(vertiblurpass);
	vertiblurState->setUniformInt("steps", 2);
	vertiblurState->retain();

	GLProgramState* combinefilterstate = GLProgramState::create(combinefilter);
	combinefilterstate->retain();

	postprocshaders.push_back(PostProcShader(brightpass, brightpassState));
	postprocshaders.push_back(PostProcShader(horiblurpass, horiblurState));
	postprocshaders.push_back(PostProcShader(vertiblurpass, vertiblurState));
	postprocshaders.push_back(PostProcShader(combinefilter, combinefilterstate));

	FrameBuffers = new RenderTexture*[postprocshaders.size() + 1];

	for (int i = 0; i < postprocshaders.size() + 1; i++)
	{
		FrameBuffers[i] = RenderTexture::create(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
		FrameBuffers[i]->getSprite()->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
		FrameBuffers[i]->retain();
		if (i < postprocshaders.size())
		{
			FrameBuffers[i]->getSprite()->setGLProgram(postprocshaders[i].shaderprog);
			FrameBuffers[i]->getSprite()->setGLProgramState(postprocshaders[i].shaderprogstate);
		}
	}

	horiblurState->setUniformTexture("image", FrameBuffers[1]->getSprite()->getTexture());
	vertiblurState->setUniformTexture("image", FrameBuffers[2]->getSprite()->getTexture());
	combinefilterstate->setUniformTexture("blurpass", FrameBuffers[3]->getSprite()->getTexture());
	combinefilterstate->setUniformTexture("original", FrameBuffers[0]->getSprite()->getTexture());

	this->retain();
	this->onEnter();
	this->onEnterTransitionDidFinish();

	Input::RegisterFunctionToActionPress(Input::InputAction::IA_UP, CC_CALLBACK_0(PostProcessing::IncrementTexture, this));

	isActive = true;

	return true;
}

void PostProcessing::SetActive(bool active)
{
	isActive = active;
}

void PostProcessing::IncrementTexture()
{
	textureID++;
	if (textureID > postprocshaders.size())
		textureID = 0;

	std::string str = "Next Texture: ";
	str += std::to_string(textureID);

	CCLOG(str.c_str());
}

void PostProcessing::Render(Node* rootNode)
{
	FrameBuffers[0]->beginWithClear(0, 0, 0, 255);
	rootNode->visit();
	FrameBuffers[0]->end();

	if (!isActive)
	{
		FinalTexture = FrameBuffers[0]->getSprite()->getTexture();
		return;
	}


	for (int i = 1; i < postprocshaders.size() + 1; i++)
	{
		FrameBuffers[i]->beginWithClear(0, 0, 0, 255);
		FrameBuffers[i - 1]->getSprite()->visit();
		FrameBuffers[i]->end();
	}

	FinalTexture = FrameBuffers[textureID]->getSprite()->getTexture();
}

cocos2d::Texture2D* PostProcessing::GetTexture()
{
	return FinalTexture;
}