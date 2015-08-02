// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#include "maze_ascii.h"


using namespace std;

bool exitPlaced = false;

void neighbors(int(&maze)[HEIGHT][WIDTH], COORD curTile, vector<int>& moves)
{
	
	if(maze[curTile.y - 2][curTile.x] == 0 && !((curTile.y - 2) <= 0))
	{
		moves.push_back(1);
	}
	if(maze[curTile.y + 2][curTile.x] == 0 && !((curTile.y + 2) >= HEIGHT))
	{
		moves.push_back(2);
	}
	if(maze[curTile.y][curTile.x - 2] == 0 && !((curTile.x - 2) <= 0))
	{
		moves.push_back(3);
	}
	if(maze[curTile.y][curTile.x + 2] == 0 && !((curTile.x + 2) >= WIDTH))
	{
		moves.push_back(4);
	}
	
	random_shuffle(moves.begin(), moves.end());
}
	

void createMaze(int(&maze)[HEIGHT][WIDTH], int row, int column)
{
	COORD curTile = {column, row};
	stack<COORD> tileList;
	tileList.push(curTile);
	
	while (!tileList.empty())
	{
	
	vector<int> moves;
	neighbors(maze, curTile, moves);

	if(!moves.empty())
	{
		COORD temp;
		switch(moves[0])
		{
			case 1: // Down
				temp.x = curTile.x;
				temp.y = curTile.y - 2;

				maze[curTile.y - 1][curTile.x] = 1;
				maze[curTile.y - 2][curTile.x] = 1;
				curTile = temp;
				tileList.push(curTile);
	
			break;
			
			case 2: // Up
				temp.x = curTile.x;
				temp.y = curTile.y + 2;

				maze[curTile.y + 1][curTile.x] = 1;
				maze[curTile.y + 2][curTile.x] = 1;
				curTile = temp;
				tileList.push(curTile);
			
			break;			

			case 3: // Left
				temp.x = curTile.x - 2;
				temp.y = curTile.y;

				maze[curTile.y][curTile.x - 1] = 1;
				maze[curTile.y][curTile.x - 2] = 1;
				curTile = temp;
				tileList.push(curTile);
			
			break;

			case 4: // Right 			
				temp.x = curTile.x + 2;
				temp.y = curTile.y;

				maze[curTile.y][curTile.x + 1] = 1;
				maze[curTile.y][curTile.x + 2] = 1;
				curTile = temp;
				tileList.push(curTile);
			
			break;	
		}
	}
	else
	{
		if (exitPlaced == false)
		{
			exitPlaced = true;
			maze[curTile.y][curTile.x] = 9;
		}
		
		curTile = tileList.top();
		tileList.pop();
	}
	}
	

	
}



void drawMaze()
{
	// Create the maze with specified height and width;
	int maze[HEIGHT][WIDTH] = { 0 };
	int row, column;

	// Initialize maze with all walls up at first
	// 1 for walls, 0 for open space
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			maze[i][j] = 0;
		}
	}

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
	maze[row][column] = 8;

	createMaze(maze, row, column);

	// Draw maze
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (maze[i][j] == 0) // Wall
			{
				cout << "@";
			}
			else if (maze[i][j] == 1) // Space
			{
				cout << " ";
			}
			else if (maze[i][j] == 8) // Start
			{
				cout << "S";
			}
			else if (maze[i][j] == 9) // End
			{
				cout << "X";
			}

		}
		cout << endl;
	}

	//delete maze;
}