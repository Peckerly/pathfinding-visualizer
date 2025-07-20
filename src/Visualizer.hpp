#pragma once

#include "Grid.hpp"

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Run();
private:
	Grid mGrid;
};