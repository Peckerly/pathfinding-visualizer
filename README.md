# Pathfinding Visualizer

## Simple program visualizing BFS and DFS algorithms, made in C++.

## Requirements
* C++20 capable compiler
* CMake 3.24+


## Building

Windows:
* Clone the repository:
```powershell
git clone https://github.com/Peckerly/pathfinding-visualizer.git
cd pathfinding-visualizer
```
* Make a build folder and run CMake:
```powershell
mkdir build
cd build
cmake ..
```

* Build the project:
```powershell
cmake --build . --config Release
```

Mac OS:
* Install CMake using Homebrew:
```zsh
brew install cmake
```
* Clone the repository:
```zsh
git clone https://github.com/Peckerly/pathfinding-visualizer.git && cd pathfinding-visualizer
```
* Make a build folder and run CMake:
```zsh
mkdir build && cd build
cmake ..
```
* Build the project:
```zsh
cmake --build . --config Release
```

## Tested compilers
* Windows: MSVC 19.44.35213.0
* Mac OS: AppleClang 17

## Libraries used
* raylib, raygui made by @raysan5