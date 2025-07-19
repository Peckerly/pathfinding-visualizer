#include "Visualizer.hpp"

#include "raylib.h"

#include <string>

static constexpr int sWidth = 1280;
static constexpr int sHeight = 720;
static const std::string sTitle = "Pathfinding Visualizer";

Visualizer::Visualizer() {
	InitWindow(sWidth, sHeight, sTitle.c_str());
}

Visualizer::~Visualizer()
{
	CloseWindow();
}

void Visualizer::Run() {
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Hello world!", sWidth / 2, sHeight / 2, 20, LIGHTGRAY);

		EndDrawing();
	}
}