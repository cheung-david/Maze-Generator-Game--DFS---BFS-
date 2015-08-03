// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#ifndef MAZE_ASCII_H
#define MAZE_ASCII_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <stack>

#define WIDTH 55
#define HEIGHT 35


// Column and rows
struct COORD
{
	int x;
	int y;
};

// Find neighbours for the current tile
void neighbors(int(&maze)[HEIGHT][WIDTH], COORD curTile, std::vector<int>& moves);

// Generate the maze
void createMaze(int(&maze)[HEIGHT][WIDTH], int row, int column);

// Draw the maze
void drawMaze();

#endif
