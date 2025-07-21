#include "Grid.hpp"

#include "raylib.h"

Grid::Grid() {
	mGridData.fill(Cell::Empty);
}

const int Grid::MarkStartOrEnd(const int x, const int y, Cell cellType) {
	auto [gridX, gridY] = ScreenToGridCoords(x, y);

	if (gridX >= 0 && gridX < sGridSize && gridY >= 0 && gridY < sGridSize) {
		const int index = sGridSize * gridY + gridX;
		mGridData[index] = cellType;
		return index;
	}
	return -1;
}

void Grid::Paint(const int x, const int y, Cell cellType) {
	auto [gridX, gridY] = ScreenToGridCoords(x, y);

	if (gridX >= 0 && gridX < sGridSize && gridY >= 0 && gridY < sGridSize) {
		const int index = sGridSize * gridY + gridX;
		mGridData[index] = cellType;
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
			case Cell::End: {
				cellColor = RED;
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