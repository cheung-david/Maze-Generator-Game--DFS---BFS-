// Maze Generator - Grid
// By David Cheung
// Class that contains all the tiles in the map in the form of a grid.

#ifndef GRID_H
#define GRID_H

#include <stack>
#include "tiles.h"
#include "maze_ascii.h"


class Grid
{
public:
	Grid();

	void initialize();

	COORD getStartPos();

	COORD getExitPos();

	COORD getPlayerPos();

	void setStartPos(int &x, int &y);

	void setExitPos(int &x, int &y);

	void setPlayerPos(int x, int y);

	void findSolution();

	bool isOpen(int x, int y);

	bool isAdjacent;

	void drawTiles();
	void drawSolution();
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