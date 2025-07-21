#pragma once

#include "Grid.hpp"

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Update();

	void DrawGUI();

	void Render();

	void Run();
private:
	Grid mGrid;

	int mStartingPoint = -1;
	int mEndingPoint = -1;

	bool mIsPathfinding = false;
};