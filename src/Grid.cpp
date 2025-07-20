#include "Grid.hpp"

#include "raylib.h"

Grid::Grid() {
	mGridData.fill(Cell::Empty);
}

void Grid::Draw() {
	for (int i = 0; i < mGridData.size(); i++)
	{
		Color cellColor;
		switch (mGridData[i])
		{
			case Cell::Empty:
			{
				cellColor = LIGHTGRAY;
				break;
			}
			default:
			{
				cellColor = BLACK;
				break;
			}
		}

		int x = (i % sGridSize) * sCellSize;
		int y = (i / sGridSize) * sCellSize;

		DrawRectangle(x, y, sCellSize, sCellSize, cellColor);
		DrawRectangleLines(x, y, sCellSize, sCellSize, BLACK);
	}
}