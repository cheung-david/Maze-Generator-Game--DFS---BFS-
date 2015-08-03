// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#include "main.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(850, 550), "Maze Game");
	//sf::RectangleShape player(sf::Vector2f(15, 15));
	sf::CircleShape player(7.5);

	player.setFillColor(sf::Color::Cyan);
	Grid maze;

	bool exitPlaced = false;
	bool startPlaced = false;
	bool solutionPlaced = false;

	// Initialize screen buffer
	std::vector<sf::RectangleShape> buffer(HEIGHT * WIDTH);

	// Draw ascii maze (console)
	drawMaze();

	// Set tile-grid coordinates
	maze.setSolidMaze();

	drawSolidMaze(maze);

	// Load tiles onto screen buffer
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int column = 0; column < WIDTH; column++)
		{
			buffer[row * WIDTH + column].setSize(sf::Vector2f(maze.getTile(row, column)->getWidth(), maze.getTile(row, column)->getWidth()));
			//std::cout << maze.getTile(row, column)->isWall() << " ";
			if (maze.getTile(row, column)->isWall())
			{
				buffer[row * WIDTH + column].setFillColor(sf::Color(255, 255, 255));
				buffer[row * WIDTH + column].setPosition(maze.getTile(row, column)->getX(), maze.getTile(row, column)->getY());
				window.draw(buffer[row * WIDTH + column]);
			}
			else
			{
				buffer[row * WIDTH + column].setFillColor(sf::Color(0, 0, 0));
				buffer[row * WIDTH + column].setPosition(maze.getTile(row, column)->getX(), maze.getTile(row, column)->getY());

				if (startPlaced == false)
				{
					startPlaced = true;
					buffer[row * WIDTH + column].setFillColor(sf::Color(255, 0, 0));
					maze.setStartPos(column, row);
				}

				if ((HEIGHT - row) < 3 && (WIDTH - column) < 5 && exitPlaced == false)
				{
					exitPlaced = true;
					buffer[row * WIDTH + column].setFillColor(sf::Color(0, 255, 0));
					maze.setExitPos(column, row);
				}
				window.draw(buffer[row * WIDTH + column]);
			}
		}
	}

	maze.setPlayerPos(maze.getStartPos().x, maze.getStartPos().y);
	player.setPosition(maze.getTile(maze.getStartPos().y, maze.getStartPos().x)->getX() , maze.getTile(maze.getStartPos().y, maze.getStartPos().x)->getY());
	
	
	// Main game loop
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();


		// Player movement - keyboard function
		// left key is pressed: move our character
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if ((maze.getPlayerPos().x - 1) > 0 && maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x - 1)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x - 1, maze.getPlayerPos().y);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{ 
			if ((maze.getPlayerPos().x + 1) < WIDTH && maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x + 1)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x + 1, maze.getPlayerPos().y);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if ((maze.getPlayerPos().y - 1) > 0 && maze.getTile(maze.getPlayerPos().y - 1, maze.getPlayerPos().x)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x, maze.getPlayerPos().y - 1);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if ((maze.getPlayerPos().y + 1) < HEIGHT && maze.getTile(maze.getPlayerPos().y + 1, maze.getPlayerPos().x)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x, maze.getPlayerPos().y + 1);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			/* Test 
			std::cout << maze.findSolution() << std::endl;
			std::cout << maze.getExitPos().x << " " << maze.getExitPos().y << std::endl;
			*/

			// Find solution - breadth first search
			maze.findSolution();

			std::stack<COORD> solution = maze.returnSolution();
			int n = solution.size() - 1;
			
			// Remove starting trace for solution
			if (!solution.empty())
			{
				solution.pop();
			}

			// Display Solution
			for (int i = 1; i < n; i++)
			{
				int solX = solution.top().x;
				int solY = solution.top().y;
				
				// Toggle solution
				if (solutionPlaced == false) // Show solution
				{ 	
					buffer[solY * WIDTH + solX].setFillColor(sf::Color(190, 0, 0));
				}
				else // Remove solution
				{
					buffer[solY * WIDTH + solX].setFillColor(sf::Color(0, 0, 0));
				}

				window.draw(buffer[solY * WIDTH + solX]);
				solution.pop();
			}

			if (solutionPlaced == false)
			{ 
				solutionPlaced = true;
			}
			else
			{
				solutionPlaced = false;
			}

			buffer[maze.getExitPos().y * WIDTH + maze.getExitPos().x].setFillColor(sf::Color(0, 255, 0));
			buffer[maze.getStartPos().y * WIDTH + maze.getStartPos().x].setFillColor(sf::Color(255, 0, 0));

			// Remove ending trace for solution
			while (!solution.empty())
			{
				solution.pop();
			}
			
			maze.initialize();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			main();
			window.close();
		}

		// Load screen buffer
		for (int row = 0; row < HEIGHT; row++)
		{
			for (int column = 0; column < WIDTH; column++)
			{
				window.draw(buffer[row * WIDTH + column]);
			}
		}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			window.draw(player);
			window.display();

		}
	
	return 0;
}
