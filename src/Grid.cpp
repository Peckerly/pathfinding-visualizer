#include "Grid.hpp"

#include "raylib.h"

Grid::Grid() {
	mGridData.fill(Cell::Empty);
}

const std::vector<int> Grid::GetAdjacentCells(const int index) const {
	std::vector<int> outVec;
	outVec.reserve(8);

	const int x = index % sGridSize;
	const int y = index / sGridSize;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) {
				continue;
			}

			const int neighborX = x + i;
			const int neighborY = y + j;

			if (IsValidIndex(neighborX, neighborY)) {
				//check if can go through corners
				if (i != 0 && j != 0) {
					int checkHorizontal = y * sGridSize + (x + i);
					int checkVertical = (y + j) * sGridSize + x;

					if (GetCellState(checkHorizontal) == Cell::Wall && GetCellState(checkVertical) == Cell::Wall) {
						continue;
					}
				}

				const int neighborIndex = neighborY * sGridSize + neighborX;
				outVec.push_back(neighborIndex);
			}
		}
	}

	return outVec;
}

const std::optional<int> Grid::MarkStartOrEnd(const int x, const int y, Cell cellType) {
	auto [gridX, gridY] = ScreenToGridCoords(x, y);

	if (IsValidIndex(gridX, gridY)) {
		const int index = sGridSize * gridY + gridX;
		if (mGridData[index] != Cell::Start && mGridData[index] != Cell::End) {
			mGridData[index] = cellType;
			return index;
		}
	}
	return {};
}


void Grid::Paint(const int x, const int y, Cell cellType) {
	auto [gridX, gridY] = ScreenToGridCoords(x, y);

	if (IsValidIndex(gridX, gridY)) {
		const int index = sGridSize * gridY + gridX;
		if (mGridData[index] == Cell::Start || mGridData[index] == Cell::End) {
			return;
		}
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
			case Cell::Visited: {
				cellColor = DARKBLUE;
				break;
			}
			case Cell::Path: {
				cellColor = ORANGE;
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

void Grid::Reset() {
	mGridData.fill(Cell::Empty);
}
