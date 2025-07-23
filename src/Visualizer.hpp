#pragma once

#include "Grid.hpp"

#include <queue>
#include <stack>
#include <map>
#include <optional>

enum class Algorithm : bool {
	BFS = 0,
	DFS
};

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Update();
	void DrawGUI();
	void Render();
	void Run();

	void InitPathfinding();
	void Pathfind();
	void Backtrace();
private:
	Grid mGrid;

	// Pathfinding

	Algorithm mSelectedAlgorithm = Algorithm::BFS;

	std::queue<int> mQueue;
	std::stack<int> mStack;

	std::map<int, int> mParentCells;

	std::optional<int> mStartPoint;
	std::optional<int> mTargetPoint;

	int mAlgorithmIndex = 0;
	bool mDropdownEditMode = false;

	bool mPathfindingLock = true;
};