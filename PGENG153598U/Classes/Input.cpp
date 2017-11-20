#include "Input.h"
#include <string>
using namespace cocos2d;

bool Input::init()
{
	if (!Node::init())
	{
		return false;
	}

	_keys.reset();
	_Prevkeys.reset();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Input::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Input::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);

	this->onEnter();
	this->scheduleUpdateWithPriority(1);
	this->retain();

	CCLOG("Input Initialized");
	return true;
}

void Input::RegisterFunctionToKeyPress(EventKeyboard::KeyCode keyCode,	std::function<void()> fptr)
{
	std::string keyStr = "KP_";
	keyStr += (int)keyCode;
	GetInstance()->FunctionMaps[keyStr].push_back(fptr);
}

void Input::RegisterFunctionToKeyRelease(EventKeyboard::KeyCode keyCode, std::function<void()> fptr)
{
	std::string keyStr = "KR_";
	keyStr += (int)keyCode;
	GetInstance()->FunctionMaps[keyStr].push_back(fptr);
}

void Input::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	_keys[(int)keyCode] = 1;

	std::string keyStr = "KP_";
	keyStr += (int)keyCode;
	for (std::vector< std::function<void()> >::iterator itr = FunctionMaps[keyStr].begin(); itr != FunctionMaps[keyStr].end(); itr++)
	{
		(*itr)();
	}
}

void Input::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	_keys[(int)keyCode] = 0;

	std::string keyStr = "KR_";
	keyStr += (int)keyCode;
	for (std::vector< std::function<void()> >::iterator itr = FunctionMaps[keyStr].begin(); itr != FunctionMaps[keyStr].end(); itr++)
	{
		(*itr)();
	}
}

bool Input::GetKey(cocos2d::EventKeyboard::KeyCode key)
{
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