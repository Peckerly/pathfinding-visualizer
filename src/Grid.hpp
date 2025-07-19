#pragma once

#include "Constants.hpp"

#include <array>

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

	const auto GetData() const { return mGridData; }

private:
	std::array<Cell, gGridSize * gGridSize> mGridData;
};