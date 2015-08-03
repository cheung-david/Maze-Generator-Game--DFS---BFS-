// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#ifndef MAZE_SFML_H
#define MAZE_SFML_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <stack>
#include "grid.h"

#define WIDTH 55
#define HEIGHT 35


// Column and rows
struct SFCOORD
{
	int x;
	int y;
};

// Find neighbours for the current tile
void neighborsSF(Grid& maze, SFCOORD curTile, std::vector<int>& moves);

// Generate the maze
void createSolidMaze(Grid& maze, int row, int column);

// Draw the maze
void drawSolidMaze(Grid& maze);

#endif
