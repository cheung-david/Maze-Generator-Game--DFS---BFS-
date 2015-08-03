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
			gridTiles[row][col].setVisited(false);

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

bool Grid::isAdjacent(int curX, int curY, int targetX, int targetY)
{
	// Not in range
	if ((targetX < 0) || (targetX >= WIDTH))
		return false;

	// Not in range
	if ((targetY < 0) || (targetY >= HEIGHT))
		return false;
	
	// If the X values are equal
	if (curX == targetX)
	{
		// Adjacent on top
		if ((curY - 1) == targetY)
			return true;

		// Adjacent below
		else if ((curY + 1) == targetY)
			return true;
	}

	// If the Y values are equal
	else if (curY == targetY)
	{
		// Adjacent to left
		if ((curX - 1) == targetX)
			return true;

		// Adjacent to right
		else if ((curX + 1) == targetX)
			return true;
	}

	return false;
}

bool Grid::isOpen(Tile tile)
{
	if (tile.isWall() == false && tile.isVisited() == false)
	//if (tile.isVisited() == false)
	{
		//std::cout << "1";
		return true;
		
	}
	else
	{
		//std::cout << "0";
		return false;
	}
}

bool Grid::findSolution()
{
	std::queue<std::stack<COORD>> mainList;
	std::stack<COORD> singlePath;

	COORD location = { startPos.x, startPos.y };
	gridTiles[startPos.y][startPos.x].setVisited(true); // Visited
	singlePath.push(location);
	mainList.push(singlePath);
	//cout << "TOP:" << mainList.front().top().Y << " " << mainList.front().top().X << endl;
	while (mainList.empty() != true)
	{
		singlePath = mainList.front();
		mainList.pop();
		location = singlePath.top();
		//cout << "TOP:" << singlePath.top().Y << " " << singlePath.top().X << endl;
		for (short row = location.y - 1; row < location.y + 2; row++)
		{
			for (short column = location.x - 1; column < location.x + 2; column++)
			{

				if (!isAdjacent(location.x, location.y, column, row))
					continue;


				//int cell = maze[row][column];
				if (isOpen(gridTiles[row][column]))
				{
					COORD temp = { column, row };

					if (temp.x == endPos.x && temp.y == endPos.y)
					{
						singlePath.push(temp);
						while (singlePath.empty() != true)
						{
							solutionPath.push(singlePath.top());
							//cout << "HERE:" << singlePath.top().Y << " - " << singlePath.top().X << endl;
							singlePath.pop();
						}
						return true;
					}
					gridTiles[row][column].setVisited(true);

					singlePath.push(temp);
					//cout << "TOP:" << singlePath.top().X << " " << singlePath.top().Y;
					mainList.push(singlePath);
					//cout << "TOP-:" << mainList.front().top().Y << " " << mainList.front().top().X << endl;
					singlePath.pop();
				}


			}
		}


	}
	return false;
}

std::stack<COORD> Grid::returnSolution()
{
	return solutionPath;
}