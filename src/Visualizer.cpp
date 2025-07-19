#include "Visualizer.hpp"
#include "Constants.hpp"

#include "raylib.h"

#include <string>

static const std::string sTitle = "Pathfinding Visualizer";

Visualizer::Visualizer() {
	InitWindow(gWindowSize, gWindowSize, sTitle.c_str());
}

Visualizer::~Visualizer()
{
	CloseWindow();
}

void Visualizer::Run() {
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(LIGHTGRAY);

		DrawGrid();
		
		EndDrawing();
	}
}

void Visualizer::DrawGrid() {
	auto& data = mGrid.GetData();
	for (int i = 0; i < data.size(); i++)
	{
		Color cellColor;
		switch (data.at(i))
		{
			case Cell::Empty:
			{
				cellColor = WHITE;
				break;
			}
			default:
			{
				cellColor = BLACK;
				break;
			}
		}

		int x = (i % gGridSize) * gCellSize;
		int y = (i / gGridSize) * gCellSize;

		DrawRectangle(x, y, gCellSize, gCellSize, cellColor);
		DrawRectangleLines(x, y, gCellSize, gCellSize, BLACK);
	}
}