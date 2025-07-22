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
	if (!mIsPathfinding) {
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
	else {
		StartPathfinding(mAlgorithmSelected);
	}
}

void Visualizer::DrawGUI() {
	DrawText("Press S to mark the starting point at the current mouse position", 1050, 100, 20, GREEN);
	DrawText("Press T to mark the target point at the current mouse position", 1050, 150, 20, RED);
	DrawText("Use your left/right mouse keys to draw/erase walls", 1050, 200, 20, WHITE);

	if (GuiDropdownBox(Rectangle{ .x = 1050, .y = 250, .width = 300, .height = 100 }, "BFS;DFS", &mAlgorithmSelected, mDropdownEditMode)) {
		mDropdownEditMode = !mDropdownEditMode;
	}

	if (GuiButton(Rectangle{ .x = 1400, .y = 250, .width = 300, .height = 100 }, "Start") && !mIsPathfinding) {
		InitPathfinding(mAlgorithmSelected);
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

void Visualizer::InitPathfinding(const int selection)
{
	switch (selection) {
		case 0: {
			mQueue.push(mStartPoint.value());
			mGrid.SetCellState(mStartPoint.value(), Cell::Visited);
			break;
		}
		case 1: {
			mStack.push(mStartPoint.value());
			mGrid.SetCellState(mStartPoint.value(), Cell::Visited);
			break;
		}
	}
	mIsPathfinding = true;
}

void Visualizer::StartPathfinding(const int selection)
{
	switch (selection) {
		case 0: {
			if (!mQueue.empty()) {
				int curr = mQueue.front();
				mQueue.pop();
				for (auto& cell : mGrid.GetAdjacentCells(curr)) {
					if (mGrid.GetCellState(cell) == Cell::End) {
						mIsPathfinding = false;
					}
					if (mGrid.GetCellState(cell) != Cell::Visited && mGrid.GetCellState(cell) != Cell::Wall) {
						mQueue.push(cell);
						mGrid.SetCellState(cell, Cell::Visited);
					}
				}
			}
			else {
				mIsPathfinding = false;
			}
			break;
		}
		case 1: {
			if (!mStack.empty()) {
				int curr = mStack.top();
				mStack.pop();
				for (auto& cell : mGrid.GetAdjacentCells(curr)) {
					if (mGrid.GetCellState(cell) == Cell::End) {
						mIsPathfinding = false;
					}
					if (mGrid.GetCellState(cell) != Cell::Visited && mGrid.GetCellState(cell) != Cell::Wall) {
						mStack.push(cell);
						mGrid.SetCellState(cell, Cell::Visited);
					}
				}
			}
			else {
				mIsPathfinding = false;
			}
			break;
		}
	}
}
