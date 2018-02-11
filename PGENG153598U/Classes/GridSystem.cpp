#include "GridSystem.h"

#include "Grid.h"

GridSystem::GridSystem()
{
}

GridSystem::~GridSystem()
{
}

void GridSystem::GenerateGrid(Size playingSize, unsigned numCol, unsigned numRow, unsigned numberofSides)
{
	gridMap.reserve(numRow);
	SetGridRows(numRow);
	SetGridColumns(numCol);

	for (int i = 0; i < numRow; i++)
	{
		vector<Grid> Player_Grid_List = vector<Grid>(numCol);
		gridMap.push_back(Player_Grid_List);
	}
	gridWidth = playingSize.width / numCol;
	gridHeight = playingSize.height / numRow;
	int halfWidth = gridWidth * 0.5f;
	int halfHeight = gridHeight * 0.5f;

	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			gridMap[i][j].SetCoord(Vec2(j, i));
			gridMap[i][j].SetIndex((i + 1) + (5 * (j)));
			if (gridMap[i][j].GetIndex() < 25)
			{
				gridMap[i][j].SetIdentity("Player_Grid");
			}
			else
			{
				gridMap[i][j].SetIdentity("Enemy_Grid");
			}
			gridMap[i][j].SetPosition(Vec2(halfWidth + (j * (int)gridWidth), halfHeight + (i * (int)gridHeight) + 100));
		}
	}
}


void GridSystem::GenerateGrid(Size playingSize, unsigned numCol, unsigned numRow, unsigned numPlayerCol, unsigned numPlayerRow)
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
			gridMap[i][j].SetPosition(Vec2(halfWidth + (j * gridWidth), halfHeight + (i * gridHeight) + 100));
			if (i < numPlayerRow && j < numPlayerCol)
				gridMap[i][j].SetBelongsToPlayer(true);
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

Grid GridSystem::GetGrid(int Index)
{
	int temprow = 0, tempcolumn = 0;
	for (int i = 0; i < G_Rows; i++)
	{
		for (int j = 0; j < G_Columns; j++)
		{
			if (gridMap[i][j].GetIndex() == Index)
			{
				temprow = i;
				tempcolumn = j;
			}
		}
	}
	return this->gridMap[temprow][tempcolumn];
}
