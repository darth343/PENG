#include "Input.h"
#include <string>
using namespace cocos2d;

//bool* Input::_keys = nullptr;

bool Input::init()
{
	if (!Node::init())
	{
		return false;
	}

	//_keys = new bool[NUM_KEYS];
	_keys.reset();
	_Prevkeys.reset();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Input::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Input::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);

	this->onEnter();
	this->scheduleUpdateWithPriority(1);
	this->retain();

	//std::memset(_keys, 0, NUM_KEYS);
	CCLOG("Input Initialized");
	return true;
}

void Input::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//std::string str = "Key Pressed";
	//str += (char)keyCode;
	//CCLOG(str.c_str());
	_keys[(int)keyCode] = 1;
}

void Input::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//CCLOG("Key Released " + (int)keyCode);
	//std::string str = "Key Released";
	//str += (char)keyCode;
	//CCLOG(str.c_str());
	_keys[(int)keyCode] = 0;
}

bool Input::GetKey(cocos2d::EventKeyboard::KeyCode key)
{
	//CCLOG("Get Key " + (int)keyCode);
	return GetInstance()->_keys[(int)key];
}

bool Input::GetKeyDown(cocos2d::EventKeyboard::KeyCode key)
{
	return GetInstance()->_keys[(int)key] && !GetInstance()->_Prevkeys[(int)key];
}

bool Input::GetKeyUp(cocos2d::EventKeyboard::KeyCode key)
{
	return !GetInstance()->_keys[(int)key] && GetInstance()->_Prevkeys[(int)key];
}


void Input::update(float delta)
{
	_Prevkeys = _keys;
}