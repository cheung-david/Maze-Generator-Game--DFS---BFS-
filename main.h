// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tiles.h"
#include "maze_ascii.h"
#include "maze_sfml.h"
#include "grid.h"
#include <chrono>
#include <thread>


// Main game loop
int main();