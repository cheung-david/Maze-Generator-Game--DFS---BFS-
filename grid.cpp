// Maze Generator - Grid
// By David Cheung
// Class that contains all the tiles in the map in the form of a grid.

#include "grid.h"

Grid::Grid()
{

}


Tile* Grid::getTile(int row, int col)
{
	return &gridTiles[row][col];
}

void Grid::setStartPos(int& x, int& y)
{
	startPos.x = x;
	startPos.y = y;
}

void Grid::setExitPos(int& x, int& y)
{
	endPos.x = x;
	endPos.y = y;
}

void Grid::setPlayerPos(int x, int y)
{
	playerPos.x = x;
	playerPos.y = y;
}

COORD Grid::getStartPos()
{
	return startPos;
}

COORD Grid::getExitPos()
{
	return endPos;
}

COORD Grid::getPlayerPos()
{
	return playerPos;
}

void Grid::initialize()
{
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int col = 0; col < WIDTH; col++)
		{
			gridTiles[row][col].setWall(true);
			gridTiles[row][col].setVisited(false);
			gridTiles[row][col].setWidth(15);
			gridTiles[row][col].setVal(0);

		}
	}
}


void Grid::setSolidMaze()
{
	int rowPos = 0;
	int colPos = 0;

	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			
			gridTiles[row][column].setY(rowPos);
			gridTiles[row][column].setX(colPos);
			colPos += gridTiles[row][column].getWidth();
			//gridTiles[row][column].draw();
			
		}
		colPos = 0;
		rowPos += gridTiles[row][0].getWidth();
	}
}