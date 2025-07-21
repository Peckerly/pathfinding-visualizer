#include "Grid.hpp"

#include "raylib.h"

Grid::Grid() {
	mGridData.fill(Cell::Empty);
}

const int Grid::ChooseStart(const int x, const int y)
{
	const int screenX = x / sCellSize;
	const int screenY = y / sCellSize;

	if (screenX >= 0 && screenX < sGridSize && screenY >= 0 && screenY < sGridSize) {
		mGridData[sGridSize * screenY + screenX] = Cell::Start;
		return sGridSize * screenY + screenX;
	}
	return -1;
}

const int Grid::ChooseEnd(const int x, const int y)
{
	const int screenX = x / sCellSize;
	const int screenY = y / sCellSize;

	if (screenX >= 0 && screenX < sGridSize && screenY >= 0 && screenY < sGridSize) {
		mGridData[sGridSize * screenY + screenX] = Cell::End;
		return sGridSize * screenY + screenX;
	}
	return -1;
}

void Grid::Paint(const int x, const int y, Cell cellType) {
	const int screenX = x / sCellSize;
	const int screenY = y / sCellSize;

	if (screenX >= 0 && screenX < sGridSize && screenY >= 0 && screenY < sGridSize) {
		mGridData[sGridSize * screenY + screenX] = cellType;
	}
}

void Grid::Draw() {
	for (int i = 0; i < mGridData.size(); i++) {
		Color cellColor;
		switch (mGridData[i]) {
			case Cell::Empty: {
				cellColor = LIGHTGRAY;
				break;
			}
			case Cell::Start: {
				cellColor = GREEN;
				break;
			}
			case Cell::Wall: {
				cellColor = DARKGRAY;
				break;
			}
			default: {
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