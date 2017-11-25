#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "cocos2d.h"

using namespace cocos2d;

#include <string>
#include <map>

class AnimationManager
{
public:
	static AnimationManager* GetInstance(const std::string& _id)
	{
		if (instance.count(_id) == 0)
			instance[_id] = new AnimationManager(_id);

		return instance[_id];
	}
	static AnimationManager* RemoveInstance(const std::string& _id)
	{
		AnimationManager* currMesh = GetInstance(_id);
		if (currMesh != NULL)
		{
			delete currMesh;
			instance.erase(_id);
		}
	}
	static void Destroy()
	{
		for (auto q : instance)
		{
			AnimationManager* currInstance = q.second;//retrieve each instance of this AnimationManager
			if (currInstance != NULL)
			{
				//clears the animMap in each instance
				for (auto r : currInstance->animMap)
				{
					currInstance->RemoveAnimate(r.first);
				}

				delete currInstance;
				instance.erase(q.first);
			}
		}
	}
	virtual ~AnimationManager();

	Action* GetAnimate(const std::string& animName);
	void AddAnimate(const std::string& animName, int startFrame, int endFrame, float animSpeed = 1.0f, bool repeat = true);
	void RemoveAnimate(const std::string& animName);

protected:
	AnimationManager(const std::string& _id);
	const std::string instanceID;

	std::unordered_map<std::string, Action*> animMap;

	static std::map<std::string, AnimationManager*> instance;
};

#endif




//#ifndef ANIMATION_MANAGER_H
//#define ANIMATION_MANAGER_H
//
//#include <string>
//#include <map>
//
//class Mesh;
//class Animation;
//
//class AnimationManager
//{
//public:
//	static AnimationManager* GetInstance(const std::string& meshName)
//	{
//		if (instance.count(meshName) == 0)
//			instance[meshName] = new AnimationManager();
//
//		return instance[meshName];
//	}
//	static AnimationManager* RemoveInstance(const std::string& meshName)
//	{
//		AnimationManager* currMesh = GetInstance(meshName);
//		if (currMesh != NULL)
//		{
//			delete currMesh;
//			instance.erase(meshName);
//		}
//	}
//	static void Destroy()
//	{
//		for (auto q : instance)
//		{
//			AnimationManager* currID = q.second;
//			if (currID != NULL)
//			{
//				delete currID;
//				instance.erase(q.first);
//			}
//		}
//	}
//	virtual ~AnimationManager();
//
//	Animation* GetAnimation(const std::string& animName);
//	void AddAnimation(const std::string& animName, Animation* anim);
//	void RemoveAnimation(const std::string& animName);
//
//protected:
//	AnimationManager();
//
//	std::map<std::string, Animation*> animMap;
//
//	static std::map<std::string, AnimationManager*> instance;
//};
//
//#endif