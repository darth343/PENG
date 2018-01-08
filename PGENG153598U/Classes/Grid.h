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

	inline virtual void SetIsOccupied(bool _flag) { this->isOccupied = _flag; }
	inline virtual bool GetIsOccupied() { return this->isOccupied; }

	inline virtual void SetBelongsToPlayer(bool _flag) { this->belongsToPlayer = _flag; }
	inline virtual bool GetBelongsToPlayer() { return this->belongsToPlayer; }

protected:
	Vec2 position;
	Vec2 coord;

	bool isOccupied;
	bool belongsToPlayer;

};

#endif