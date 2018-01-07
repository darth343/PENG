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

	void GenerateGrid(Size playingSize, unsigned numCol, unsigned numRow, unsigned numberofsides);

	virtual Grid GetGrid(int col, int row);

	virtual Grid GetGrid(int Index);

	bool CheckGrid(Vec2 position);

	inline virtual float GetGridWidth() { return this->gridWidth; }
	inline virtual float GetGridHeight() { return this->gridHeight; }

	void SetGridRows(int _Rows) { this->G_Rows = _Rows; };
	void SetGridColumns(int _Columns) { this->G_Columns = _Columns; };
	int GetGridRows() { return this->G_Rows; };
	int GetGridColumns() { return this->G_Columns; };

	void SetActive_Index(int Index) { this->Active_Index = Index; }
	int GetActive_Index() {	return this->Active_Index;}
protected:
	GridSystem();

	std::vector<std::vector<Grid>> gridMap;
	float gridWidth, gridHeight;
	Vec2 maxGridCount;

	int G_Rows, G_Columns;
	int Active_Index;
};

#endif