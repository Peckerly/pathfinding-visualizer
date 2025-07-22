#pragma once

#include "Grid.hpp"

#include <thread>
#include <queue>
#include <stack>

#include <optional>

class Visualizer {
public:
	Visualizer();
	~Visualizer();

	void Update();
	void DrawGUI();
	void Render();
	void Run();

	void InitPathfinding(const int selection);
	void StartPathfinding(const int selection);

	void BFS();
private:
	Grid mGrid;


	// Pathfinding
	std::thread mPathfindingThread;

	std::queue<int> mQueue;
	std::stack<int> mStack;

	std::optional<int> mStartPoint;
	std::optional<int> mTargetPoint;

	int mAlgorithmSelected = 0;
	bool mDropdownEditMode = false;

	bool mIsPathfinding = false;
};