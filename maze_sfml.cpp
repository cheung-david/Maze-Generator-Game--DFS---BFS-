#include "maze_sfml.h"

using namespace std;



void neighborsSF(Grid& maze, SFCOORD curTile, vector<int>& moves)
{
	//cout << maze.getTile(curTile.y - 2, curTile.x)->isWall();
	//cout << maze.getTile(curTile.y + 2, curTile.x)->isWall();

	if (maze.getTile(curTile.y - 2, curTile.x)->isWall() && !((curTile.y - 2) <= 0))
	{
		moves.push_back(1);
	}
	if (maze.getTile(curTile.y + 2, curTile.x)->isWall() && !((curTile.y + 2) >= HEIGHT))
	{
		moves.push_back(2);
	}
	if (maze.getTile(curTile.y, curTile.x - 2)->isWall() && !((curTile.x - 2) <= 0))
	{
		moves.push_back(3);
	}
	if (maze.getTile(curTile.y, curTile.x + 2)->isWall() && !((curTile.x + 2) >= WIDTH))
	{
		moves.push_back(4);
	}

	random_shuffle(moves.begin(), moves.end());
}


void createSolidMaze(Grid& maze, int row, int column)
{
	SFCOORD curTile = { column, row };
	stack<SFCOORD> tileList;
	tileList.push(curTile);

	while (!tileList.empty())
	{

		vector<int> moves;
		neighborsSF(maze, curTile, moves);

		if (!moves.empty())
		{
			SFCOORD temp;
			switch (moves[0])
			{
			case 1: // Down
				temp.x = curTile.x;
				temp.y = curTile.y - 2;

				maze.getTile(curTile.y - 1, curTile.x)->setWall(false);
				maze.getTile(curTile.y - 2, curTile.x)->setWall(false);

				//cout << maze.getTile(row - 1, column)->isWall();
				//cout << maze.getTile(row - 2, column)->isWall();
				curTile = temp;
				tileList.push(curTile);

				break;

			case 2: // Up
				temp.x = curTile.x;
				temp.y = curTile.y + 2;

				maze.getTile(curTile.y + 1, curTile.x)->setWall(false);
				maze.getTile(curTile.y + 2, curTile.x)->setWall(false);
				curTile = temp;
				tileList.push(curTile);

				break;

			case 3: // Left
				temp.x = curTile.x - 2;
				temp.y = curTile.y;

				maze.getTile(curTile.y, curTile.x - 1)->setWall(false);
				maze.getTile(curTile.y, curTile.x - 2)->setWall(false);
				curTile = temp;
				tileList.push(curTile);

				break;

			case 4: // Right 			
				temp.x = curTile.x + 2;
				temp.y = curTile.y;

				maze.getTile(curTile.y, curTile.x + 1)->setWall(false);
				maze.getTile(curTile.y, curTile.x + 2)->setWall(false);
				curTile = temp;
				tileList.push(curTile);

				break;
			}
		}
		else
		{
			curTile = tileList.top();
			tileList.pop();
		}
	}
}
	

void drawSolidMaze(Grid& maze)
{
	int row, column;

	srand(time(NULL));
	// Assign random starting point

	column = rand() % WIDTH;
	row = rand() % HEIGHT;
	while (row % 2 == 0) {
		row = rand() % HEIGHT;
	}

	while (column % 2 == 0) {
		column = rand() % WIDTH;
	}

	// Starting point
	//maze.getTile(row, column)->setVal(8);
	maze.getTile(row, column)->setWall(false);
	maze.setStartPos(row, column);
	cout << maze.getTile(row, column)->isWall() << endl;
	
	
	createSolidMaze(maze, row, column);

	//delete maze;
}