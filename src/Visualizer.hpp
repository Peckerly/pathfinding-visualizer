#pragma once

#include "Grid.hpp"

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Run();

	void DrawGrid();

private:
	Grid mGrid;
};