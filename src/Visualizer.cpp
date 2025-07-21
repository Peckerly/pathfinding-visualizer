#include "Visualizer.hpp"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string>

static constexpr int sWindowWidth = 1500;
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

		if (IsKeyPressed(KEY_S) && mStartingPoint == -1) {
			mStartingPoint = mGrid.MarkStartOrEnd(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::Start);
		} else if (IsKeyPressed(KEY_T) && mEndingPoint == -1) {
			mEndingPoint = mGrid.MarkStartOrEnd(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), Cell::End);
		}
	}
}

void Visualizer::DrawGUI() {
	DrawText("Choose drawing mode:", 1100, 100, 25, WHITE);
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