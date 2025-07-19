cmake_minimum_required (VERSION 3.24)

project ("pathfinding-visualizer")

add_executable (pathfinding-visualizer "src/pathfinding-visualizer.cpp" )
target_compile_features (pathfinding-visualizer PRIVATE cxx_std_23)