#include "AnimationManager.h"
#include "SpriteManager.h"

std::map<std::string, AnimationManager*> AnimationManager::instance;

AnimationManager::AnimationManager(const std::string& _id) :
	instanceID(_id)
{
}

AnimationManager::~AnimationManager()
{
}

Action* AnimationManager::GetAnimate(const std::string& animName)
{
	if (animMap.count(animName) != 0)
		return animMap[animName]->clone();
	else
		return NULL;
}

void AnimationManager::AddAnimate(const std::string& animName, int startFrame, int endFrame, float animSpeed, bool repeat)
{
	int numFrame = endFrame - startFrame + 1;
	if (numFrame <= 0)
	{
		cocos2d::log("AnimationManager::AddAnimation-> %s animation's Endframe < StartFrame", animName);
		return;
	}

	Vector<SpriteFrame*> animList(numFrame);
	for (int i = startFrame; i <= endFrame; ++i)
	{
		SpriteFrame* sprite = SpriteManager::GetInstance()->GetSpriteFrame(instanceID, i);
		animList.pushBack(sprite);
	}
	
	float timeBetweenFrames = animSpeed / numFrame;
	Animation* animation = Animation::createWithSpriteFrames(animList, timeBetweenFrames);
	ActionInterval* animate = Animate::create(animation);
	if (repeat)
		animate = RepeatForever::create(animate);

	// Clean up first if there is an existing animate with the same name
	RemoveAnimate(animName);

	// Add the mesh now
	animate->retain();
	animMap[animName] = animate;
}

void AnimationManager::RemoveAnimate(const std::string& animName)
{
	//Action* animate = GetAnimate(animName);
	//if (animate != nullptr)
	//{
	//	animate->release();
	//	animMap.erase(animName);
	//}
}





//#include "AnimationManager.h"
//#include "Animation.h"
//
//std::map<std::string, AnimationManager*> AnimationManager::instance;
//
//AnimationManager::AnimationManager()
//{
//}
//
//AnimationManager::~AnimationManager()
//{
//}
//
//Animation* AnimationManager::GetAnimation(const std::string& animName)
//{
//	if (animMap.count(animName) != 0)
//		return animMap[animName];
//	else
//		return NULL;
//}
//
//void AnimationManager::AddAnimation(const std::string& animName, Animation* anim)
//{
//	// Trivial Rejection : Invalid pointer provided
//	if (anim == NULL)
//		return;
//
//	// Clean up first if there is an existing mesh with the same name
//	RemoveAnimation(animName);
//
//	// Add the mesh now
//	animMap[animName] = anim;
//}
//
//void AnimationManager::RemoveAnimation(const std::string& animName)
//{
//	Animation* currMesh = GetAnimation(animName);
//	if (currMesh != nullptr)
//	{
//		delete currMesh;
//		animMap.erase(animName);
//	}
//}