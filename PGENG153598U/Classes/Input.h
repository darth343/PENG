#ifndef _INPUT_
#define _INPUT_

#define NUM_KEYS 200

#include <bitset>
#include <map>
#include <vector>
#include "cocos2d.h"
#include "SingletonNodeTemplate.h"
#include <functional>

using std::bitset;


class Input : public SingletonNode<Input>
{
	friend SingletonNode<Input>;
public:
	enum InputAction
	{
		IA_NONE = 0,
		IA_UP,
		IA_DOWN,
		IA_LEFT,
		IA_RIGHT,

		IA_START,
		IA_BACK,
		IA_TOTAL,
	};


private:
	std::map<cocos2d::EventKeyboard::KeyCode, InputAction> InputMaps;
	std::map<std::string, std::vector<std::function<void()> > > ActionMaps;


	// Keyboard key variables
	bitset<NUM_KEYS> _keys;
	bitset<NUM_KEYS> _Prevkeys;

public:
	//CREATE_FUNC(Input);
	virtual bool init();

	// Methods
	// -- Keyboard Input
	static bool GetKey(cocos2d::EventKeyboard::KeyCode key);
	static bool GetKeyDown(cocos2d::EventKeyboard::KeyCode key);
	static bool GetKeyUp(cocos2d::EventKeyboard::KeyCode key);

	static void AssignHotkey(Input::InputAction action, cocos2d::EventKeyboard::KeyCode hotkey);

	static void RegisterFunctionToActionPress(Input::InputAction action, std::function<void()> fptr);
	static void RegisterFunctionToActionRelease(Input::InputAction action, std::function<void()> fptr);

	// Callbackss
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);

	virtual void update(float delta);
};

#endif