#pragma once

#include "Grid.hpp"

enum class Stage : uint8_t {
	PaintWalls = 0,
	ChooseStart,
	ChooseEnd,
	WaitForInput,
	Pathfinding,
	Finished
};

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Update();
	void Render();

	void Run();
private:
	Grid mGrid;

	Stage mVisState = Stage::PaintWalls;
};