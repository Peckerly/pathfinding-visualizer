#pragma once

#include "Grid.hpp"

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Update();
	void Render();

	void Run();
private:
	Grid mGrid;
};