#include "Visualizer.hpp"

#include "raylib.h"

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
	switch (mVisState) {
		case Stage::PaintWalls: {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				auto mousePos = GetMousePosition();
				mGrid.Paint(mousePos.x, mousePos.y, Cell::Wall);
			}
			break;
		}
		default: {
			break;
		}
	}
}

void Visualizer::Render() {
	BeginDrawing();

	ClearBackground(BLACK);
	mGrid.Draw();

	EndDrawing();
}

void Visualizer::Run() {
	while (!WindowShouldClose())
	{
		Update();
		Render();
	}
}