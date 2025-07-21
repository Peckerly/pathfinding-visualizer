#pragma once

#include <array>

static constexpr int sGridSize = 50;
// Cell size is equal to 20, because we don't want to render the grid on the whole screen. We're leaving space for the GUI.
static constexpr int sCellSize = 20;

enum class Cell : uint8_t {
	Empty = 0,
	Invalid,
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

	const int ChooseStart(const int x, const int y);
	const int ChooseEnd(const int x, const int y);

	void Paint(const int x, const int y, Cell cellType);

	void Draw();

private:
	std::array<Cell, sGridSize * sGridSize> mGridData;
};