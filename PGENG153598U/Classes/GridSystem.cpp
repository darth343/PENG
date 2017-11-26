#include "GridSystem.h"

#include "Grid.h"

GridSystem::GridSystem()
{
}

GridSystem::~GridSystem()
{
}

void GridSystem::GenerateGrid(Size playingSize, unsigned numCol, unsigned numRow)
{
	maxGridCount.x = numCol;
	maxGridCount.y = numRow;

	gridMap.reserve(numRow);
	for (int i = 0; i < numRow; ++i)
	{
		std::vector<Grid> gridList = std::vector<Grid>(numCol);
		gridMap.push_back(gridList);
	}

	gridWidth = playingSize.width / numCol;
	gridHeight = playingSize.height / numRow;
	float halfWidth = gridWidth * 0.5f;
	float halfHeight = gridHeight * 0.5f;

	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			gridMap[i][j].SetCoord(Vec2(j, i));
			gridMap[i][j].SetPosition(Vec2(halfWidth + (j * gridWidth), halfHeight + (i * gridHeight)));
		}
	}
}

Grid GridSystem::GetGrid(int col, int row)
{
	int currCol = col;
	int currRow = row;

	//if (currCol >= maxGridCount.x)
	//	currCol = maxGridCount.x - 1;
	//if (currCol < 0)
	//	currCol = 0;
	//if (currRow >= maxGridCount.y)
	//	currRow = maxGridCount.y - 1;
	//if (currRow < 0)
	//	currRow = 0;

	return this->gridMap[currRow][currCol];
}