// Maze Generator - Grid
// By David Cheung
// Class that contains all the tiles in the map in the form of a grid.

#include "grid.h"

Grid::Grid()
{

}


Tile Grid::getTile(int row, int col)
{
	return gridTiles[row][col];
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
			colPos += gridTiles[row][column].getWidth();
			gridTiles[row][column].setY(rowPos);
			gridTiles[row][column].setX(colPos);
			//gridTiles[row][column].draw();
			
		}
		colPos = 0;
		rowPos += gridTiles[row][0].getWidth();
	}
}