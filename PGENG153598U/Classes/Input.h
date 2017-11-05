#ifndef _INPUT_
#define _INPUT_

#define NUM_KEYS 200

#include <bitset>
#include "cocos2d.h"
#include "SingletonNodeTemplate.h"

using std::bitset;

class Input : public SingletonNode<Input>
{
	friend SingletonNode<Input>;
private:
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
	// -- Touch Input
	


	// Callbacks
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* evnt);

	virtual void update(float delta);
};

#endif