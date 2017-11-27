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
	
	AssignHotkey(InputAction::IA_UP, EventKeyboard::KeyCode::KEY_W);
	AssignHotkey(InputAction::IA_DOWN, EventKeyboard::KeyCode::KEY_S);
	AssignHotkey(InputAction::IA_LEFT, EventKeyboard::KeyCode::KEY_A);
	AssignHotkey(InputAction::IA_RIGHT, EventKeyboard::KeyCode::KEY_D);0


	this->onEnter();
	this->scheduleUpdateWithPriority(1);
	this->retain();

	CCLOG("Input Initialized");
	return true;
}

void Input::AssignHotkey(Input::InputAction action, cocos2d::EventKeyboard::KeyCode hotkey)
{
	GetInstance()->InputMaps[hotkey] = action;
}

void Input::RegisterFunctionToActionPress(Input::InputAction action, std::function<void()> fptr)
{
	std::string keyStr = "AP_";
	keyStr += (int)action;
	GetInstance()->ActionMaps[keyStr].push_back(fptr);
}

void Input::RegisterFunctionToActionRelease(Input::InputAction action, std::function<void()> fptr)
{
	std::string keyStr = "AR_";
	keyStr += (int)action;
	GetInstance()->ActionMaps[keyStr].push_back(fptr);
}

void Input::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	_keys[(int)keyCode] = 1;

	if (InputMaps.count(keyCode) == 0)
		return;

	InputAction action = InputMaps[keyCode];

	std::string keyStr = "AP_";
	keyStr += (int)action;
	for (std::vector< std::function<void()> >::iterator itr = ActionMaps[keyStr].begin(); itr != ActionMaps[keyStr].end(); itr++)
	{
		(*itr)();
	}
}

void Input::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	_keys[(int)keyCode] = 0;

	if (InputMaps.count(keyCode) == 0)
		return;

	InputAction action = InputMaps[keyCode];


	std::string keyStr = "AR_";
	keyStr += (int)action;
	for (std::vector< std::function<void()> >::iterator itr = ActionMaps[keyStr].begin(); itr != ActionMaps[keyStr].end(); itr++)
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