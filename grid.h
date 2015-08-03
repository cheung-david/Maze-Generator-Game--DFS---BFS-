// Maze Generator - Grid
// By David Cheung
// Class that contains all the tiles in the map in the form of a grid.

#ifndef GRID_H
#define GRID_H

#include <stack>
#include <queue>
#include "tiles.h"
#include "maze_ascii.h"


class Grid
{
public:
	// Constructor
	Grid();

	void initialize();

	// Setters/getters

	COORD getStartPos();

	COORD getExitPos();

	COORD getPlayerPos();

	void setStartPos(int &x, int &y);

	void setExitPos(int &x, int &y);

	void setPlayerPos(int x, int y);

	bool findSolution();

	bool isOpen(Tile tile);

	bool isAdjacent(int curX, int curY, int targetX, int targetY);

	void drawTiles();

	std::stack<COORD> Grid::returnSolution();

	// Set tiles of corresponding width on the grid
	void setSolidMaze();

	Tile* getTile(int row, int col);

private:
	Tile gridTiles[HEIGHT][WIDTH];
	bool exitFound;
	COORD startPos;
	COORD endPos;
	COORD playerPos;

	std::stack<COORD> solutionPath;


};

#endif