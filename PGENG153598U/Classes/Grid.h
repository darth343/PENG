#ifndef GRID_H
#define GRID_H

#include "cocos2d.h"

using namespace cocos2d;

class Grid
{
public:
	Grid();
	~Grid();

	inline virtual void SetPosition(Vec2 _pos) { this->position = _pos; }
	inline virtual Vec2 GetPosition() { return this->position; }

	inline virtual void SetCoord(Vec2 _coord) { this->coord = _coord; }
	inline virtual Vec2 GetCoord() { return this->coord; }

protected:
	Vec2 position;
	Vec2 coord;

};

#endif