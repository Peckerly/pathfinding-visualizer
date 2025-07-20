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

void Visualizer::Run() {
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);
		mGrid.Draw();
		
		EndDrawing();
	}
}