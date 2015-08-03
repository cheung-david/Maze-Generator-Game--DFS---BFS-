// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#include "main.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(850, 550), "Maze Game");
	sf::RectangleShape player(sf::Vector2f(15, 15));
	player.setFillColor(sf::Color::Blue);
	Grid maze;

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
				window.draw(buffer[row * WIDTH + column]);
			}
		}
	}
	
	player.setPosition(maze.getTile(maze.getStartPos().x, maze.getStartPos().y)->getX() , maze.getTile(maze.getStartPos().x, maze.getStartPos().y)->getY());
	
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

		for (int row = 0; row < HEIGHT; row++)
		{
			for (int column = 0; column < WIDTH; column++)
			{
				window.draw(buffer[row * WIDTH + column]);
			}
		}	
			window.draw(player);
			window.display();

		}
	
	return 0;
}
