#ifndef SINGLETON_NODE_TEMPLATE_H
#define SINGLETON_NODE_TEMPLATE_H
#include "cocos2d.h"


template <typename T>
class SingletonNode : public cocos2d::Node
{
public:
	virtual bool init() = 0;

	static T* GetInstance()
	{
		if (s_mInstance == nullptr)
		{
			s_mInstance = new T();
			if (s_mInstance->init())
			{
				s_mInstance->retain();
			}
		}

		return s_mInstance;
	}

	static void Destroy()
	{
		if (s_mInstance)
		{
			delete s_mInstance;
			s_mInstance = nullptr;
		}
	}

protected:
	SingletonNode(){};
	virtual ~SingletonNode(){};

private:
	static T* s_mInstance;
};

template <typename T>
T* SingletonNode<T>::s_mInstance = nullptr;

#endif // SINGLETON_NODE_TEMPLATE_H