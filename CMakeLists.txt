cmake_minimum_required (VERSION 3.24)

set (CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/.cache/CPM)

project ("pathfinding-visualizer")

include(cmake/CPM.cmake)

CPMAddPackage(
	GITHUB_REPOSITORY "raysan5/raylib"
	GIT_TAG 5.5
	GIT_SHALLOW TRUE
)

CPMAddPackage(
	GITHUB_REPOSITORY "raysan5/raygui"
	GIT_TAG 4.0
	GIT_SHALLOW TRUE
	DOWNLOAD_ONLY TRUE
)

if (raygui_ADDED)
	add_library (raygui INTERFACE IMPORTED)
	target_include_directories (raygui INTERFACE ${raygui_SOURCE_DIR}/src)
endif()

add_executable (pathfinding-visualizer "src/main.cpp"  "src/Visualizer.cpp" "src/Visualizer.hpp" "src/Grid.cpp" "src/Grid.hpp" "src/Constants.hpp")
target_compile_features (pathfinding-visualizer PRIVATE cxx_std_23)
target_link_libraries (pathfinding-visualizer PRIVATE raylib raygui)