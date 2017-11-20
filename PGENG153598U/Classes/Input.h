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
private:
	
	std::map<std::string, std::vector<std::function<void()> > > FunctionMaps;

	// Keyboard key variables
	bitset<NUM_KEYS> _keys;
	bitset<NUM_KEYS> _Prevkeys;
	// Touch variables
	int touchCount;


public:
	//CREATE_FUNC(Input);
	virtual bool init();

	// Methods
	// -- Keyboard Input
	static bool GetKey(cocos2d::EventKeyboard::KeyCode key);
	static bool GetKeyDown(cocos2d::EventKeyboard::KeyCode key);
	static bool GetKeyUp(cocos2d::EventKeyboard::KeyCode key);

	static void RegisterFunctionToKeyPress(cocos2d::EventKeyboard::KeyCode key, std::function<void()> fptr);
	static void RegisterFunctionToKeyRelease(cocos2d::EventKeyboard::KeyCode key, std::function<void()> fptr);

	// -- Touch Input
	


	// Callbacks
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);

	virtual void update(float delta);
};

#endif