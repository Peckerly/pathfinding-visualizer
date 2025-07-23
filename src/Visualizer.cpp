#include "Visualizer.hpp"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string>

static constexpr int sWindowWidth = 1800;
static constexpr int sWindowHeight = 1000;

static const std::string sTitle = "Pathfinding Visualizer";

Visualizer::Visualizer() {
	InitWindow(sWindowWidth, sWindowHeight, sTitle.c_str());
}

Visualizer::~Visualizer()
{
	CloseWindow();
}

void Visualizer::Update() {
	if (mPathfindingLock && mParentCells.empty()) {
		auto mousePos = GetMousePosition();
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			mGrid.Paint(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::Wall);
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			mGrid.Paint(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::Empty);
		}

		if (IsKeyPressed(KEY_S) && !mStartPoint.has_value()) {
			mStartPoint = mGrid.MarkStartOrEnd(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::Start);
		} else if (IsKeyPressed(KEY_T) && !mTargetPoint.has_value()) {
			mTargetPoint = mGrid.MarkStartOrEnd(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::End);
		}
	}
	Pathfind();
}

void Visualizer::DrawGUI() {
	DrawText("Press S to mark the starting point at the current mouse position", 1050, 100, 20, GREEN);
	DrawText("Press T to mark the target point at the current mouse position", 1050, 150, 20, RED);
	DrawText("Use your left/right mouse keys to draw/erase walls", 1050, 200, 20, WHITE);

	if (GuiDropdownBox(Rectangle{ .x = 1050, .y = 250, .width = 300, .height = 100 }, "BFS;DFS", &mAlgorithmIndex, mDropdownEditMode)) {
		mDropdownEditMode = !mDropdownEditMode;
		mSelectedAlgorithm = static_cast<Algorithm>(mAlgorithmIndex);
	}

	if (GuiButton(Rectangle{ .x = 1400, .y = 250, .width = 300, .height = 100 }, "Start") && mPathfindingLock) {
		InitPathfinding();
	}
}

void Visualizer::Render() {
	BeginDrawing();

	ClearBackground(BLACK);
	mGrid.Draw();
	DrawGUI();

	EndDrawing();
}

void Visualizer::Run() {
	while (!WindowShouldClose())
	{
		Update();
		Render();
	}
}

void Visualizer::InitPathfinding()
{
	if (!mStartPoint.has_value() && !mTargetPoint.has_value()) {
		return;
	}

	if (!mParentCells.empty()) {
		return;
	}

	switch (mSelectedAlgorithm) {
		case Algorithm::BFS: {
			mQueue.push(mStartPoint.value());
			mGrid.SetCellState(mStartPoint.value(), Cell::Visited);
			break;
		}
		case Algorithm::DFS: {
			mStack.push(mStartPoint.value());
			mGrid.SetCellState(mStartPoint.value(), Cell::Visited);
			break;
		}
	}
	mPathfindingLock = false;
}

void Visualizer::Pathfind()
{
	if (mPathfindingLock) {
		return;
	}

	switch (mSelectedAlgorithm) {
		case Algorithm::BFS: {
			if (!mQueue.empty()) {
				int curr = mQueue.front();
				mQueue.pop();
				for (auto& cell : mGrid.GetAdjacentCells(curr)) {
					if (cell == mTargetPoint.value()) {
						mPathfindingLock = true;
						mParentCells[cell] = curr;
						Backtrace();
						return;
					}
					if (mGrid.GetCellState(cell) != Cell::Visited && mGrid.GetCellState(cell) != Cell::Wall) {
						mQueue.push(cell);
						mParentCells[cell] = curr;
						mGrid.SetCellState(cell, Cell::Visited);
					}
				}
			}
			else {
				mPathfindingLock = true;
			}
			break;
		}
		case Algorithm::DFS: {
			if (!mStack.empty()) {
				int curr = mStack.top();
				mStack.pop();
				for (auto& cell : mGrid.GetAdjacentCells(curr)) {
					if (cell == mTargetPoint.value()) {
						mPathfindingLock = true;
						mParentCells[cell] = curr;
						Backtrace();
						break;
					}
					if (mGrid.GetCellState(cell) != Cell::Visited && mGrid.GetCellState(cell) != Cell::Wall) {
						mStack.push(cell);
						mParentCells[cell] = curr;
						mGrid.SetCellState(cell, Cell::Visited);
					}
				}
			}
			else {
				mPathfindingLock = true;
			}
			break;
		}
	}
}

void Visualizer::Backtrace() {
	if (mParentCells.count(mTargetPoint.value())) {
		int curr = mTargetPoint.value();
		while (curr != mStartPoint.value()) {
			curr = mParentCells.at(curr);
			mGrid.SetCellState(curr, Cell::Path);
		}
		mGrid.SetCellState(curr, Cell::Start);
	}
}
