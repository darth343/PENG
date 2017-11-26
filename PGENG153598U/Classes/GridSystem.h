#ifndef GRID_SYSTEM_H
#define GRID_SYSTEM_H

#include "cocos2d.h"
#include "SingletonTemplate.h"

using namespace cocos2d;

#include <vector>
using std::vector;

#include "Grid.h"
class GridSystem : public Singleton<GridSystem>
{
	friend Singleton<GridSystem>;
public:
	virtual ~GridSystem();

	void GenerateGrid(Size playingSize, unsigned numCol, unsigned numRow);

	virtual Grid GetGrid(int col, int row);
	inline virtual float GetGridWidth() { return this->gridWidth; }
	inline virtual float GetGridHeight() { return this->gridHeight; }

protected:
	GridSystem();

	std::vector<std::vector<Grid>> gridMap;
	float gridWidth, gridHeight;
	Vec2 maxGridCount;
};

#endif