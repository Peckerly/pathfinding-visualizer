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

	void Draw();

private:
	std::array<Cell, sGridSize * sGridSize> mGridData;
};