#pragma once

#include <array>
#include <vector>
#include <optional>

static constexpr int sGridSize = 50;
// Cell size is equal to 20, because we don't want to render the grid on the whole screen. We're leaving space for the GUI.
static constexpr int sCellSize = 20;

enum class Cell : uint8_t {
	Empty = 0,
	Path,
	Visited,
	Start,
	End,
	Wall
};

class Grid {
public:
	Grid();
	~Grid() = default;

	Cell GetCellState(const int index) const { return mGridData[index]; }
	void SetCellState(const int index, Cell cellState) { mGridData[index] = cellState; }

	const std::vector<int> GetAdjacentCells(const int index) const;

	const std::optional<int> MarkStartOrEnd(const int x, const int y, Cell cellType);

	void Paint(const int x, const int y, Cell cellType);

	void Draw();

	void Reset();
private:
	const std::pair<int, int> ScreenToGridCoords(const int x, const int y) const { return { x / sCellSize, y / sCellSize }; }

	const bool IsValidIndex(const int index) const { return index >= 0 && index < sGridSize * sGridSize; }
	const bool IsValidIndex(const int x, const int y) const { return x >= 0 && x < sGridSize && y >= 0 && y < sGridSize; }

	std::array<Cell, sGridSize * sGridSize> mGridData;
};