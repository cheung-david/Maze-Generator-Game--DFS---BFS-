// Maze Generator
// By David Cheung
// Uses depth first search, recursive backtrack method to randomly generate a maze.
// Uses breadth first search to find the shortest path from the start of the maze
// to the end destination.

#include "main.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1180, 550), "Maze Game - By: David Cheung");
	//sf::RectangleShape player(sf::Vector2f(15, 15));
	sf::CircleShape player(7.5);

	player.setFillColor(sf::Color::Cyan);
	Grid maze;

	bool exitPlaced = false;
	bool startPlaced = false;
	bool solutionPlaced = false;
	bool winner = false;
	bool focus = true;

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
		// Window focus

		/* Draw instructions */
		sf::Font font;
		if (!font.loadFromFile("arial.ttf"))
		{
			// error
		}

		sf::Text text;

		// select the font
		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("~ Welcome Traveller! ~");
		text.setCharacterSize(25);
		text.setColor(sf::Color::White);
		text.setPosition(WIDTH * 15.8, 50);

		sf::Text text1;

		// select the font
		text1.setFont(font); // font is a sf::Font

		// set the string to display
		text1.setString("Use ASDW or arrow keys to move.");
		text1.setCharacterSize(15);
		text1.setColor(sf::Color::White);
		text1.setPosition(WIDTH * 15.8, 80);

		sf::Text text2;

		// select the font
		text2.setFont(font); // font is a sf::Font

		// set the string to display
		text2.setString("Your goal is to reach the green block.");
		text2.setCharacterSize(15);
		text2.setColor(sf::Color::White);
		text2.setPosition(WIDTH * 15.8, 100);

		sf::Text text3;

		// select the font
		text3.setFont(font); // font is a sf::Font

		// set the string to display
		text3.setString("Press 'P' to find the solution.");
		text3.setCharacterSize(15);
		text3.setColor(sf::Color::White);
		text3.setPosition(WIDTH * 15.8, 130);

		sf::Text text4;

		// select the font
		text4.setFont(font); // font is a sf::Font

		// set the string to display
		text4.setString("Press 'R' to generate a new maze.");
		text4.setCharacterSize(15);
		text4.setColor(sf::Color::White);
		text4.setPosition(WIDTH * 15.8, 150);

		sf::Text text5;

		// select the font
		text5.setFont(font); // font is a sf::Font

		// set the string to display
		text5.setString("Use the mouse if you want to cheat. >:)");
		text5.setCharacterSize(15);
		text5.setColor(sf::Color::Red);
		text5.setPosition(WIDTH * 15.8, 170);
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Window Focus
		if (event.type == sf::Event::GainedFocus) focus = true;
		if (event.type == sf::Event::LostFocus) focus = false;

		// Refresh Screen
		window.clear();


		// Player movement - keyboard function
		// left key is pressed: move our character
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && focus)
		{
			if ((maze.getPlayerPos().x - 1) > 0 && maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x - 1)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x - 1, maze.getPlayerPos().y);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && focus)
		{ 
			if ((maze.getPlayerPos().x + 1) < WIDTH && maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x + 1)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x + 1, maze.getPlayerPos().y);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && focus)
		{
			if ((maze.getPlayerPos().y - 1) > 0 && maze.getTile(maze.getPlayerPos().y - 1, maze.getPlayerPos().x)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x, maze.getPlayerPos().y - 1);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && focus)
		{
			if ((maze.getPlayerPos().y + 1) < HEIGHT && maze.getTile(maze.getPlayerPos().y + 1, maze.getPlayerPos().x)->isWall() == false)
			{
				maze.setPlayerPos(maze.getPlayerPos().x, maze.getPlayerPos().y + 1);
				player.setPosition(maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getX(), maze.getTile(maze.getPlayerPos().y, maze.getPlayerPos().x)->getY());
				//std::cout << maze.getPlayerPos().x << " " << maze.getPlayerPos().y << std::endl;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && focus)
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

			// Redraw starting and end points
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && focus) // Generate new maze
		{
			main();
			window.close();
		}


		// Control Character with mouse (cheat)
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				player.setPosition(localPosition.x, localPosition.y);
				//std::cout << localPosition.x << " " << localPosition.y << std::endl;
				maze.setPlayerPos((int)(localPosition.x / 15), (int)(localPosition.y / 15));
			}
		}



		// Load screen buffer
		for (int row = 0; row < HEIGHT; row++)
		{
			for (int column = 0; column < WIDTH; column++)
			{
				window.draw(buffer[row * WIDTH + column]);
			}
		}

		// Player made it to exit point
		if (maze.getPlayerPos().x == maze.getExitPos().x && maze.getPlayerPos().y == maze.getExitPos().y)
		{
			for (int row = 0; row < HEIGHT; row++)
			{
				for (int column = 0; column < WIDTH; column++)
				{
					buffer[row * WIDTH + column].setFillColor(sf::Color(0, 0, 0));
					window.draw(buffer[row * WIDTH + column]);
				}
			}
			winner = true;
			std::cout << "Congratualations, you escaped the maze!" << std::endl;
		}
			// Winner Text
			sf::Text congrats;

			// select the font
			congrats.setFont(font); // font is a sf::Font

			// set the string to display
			congrats.setString("Congratualations, you escaped the maze! Winner!!! Press 'R' to play again. :D");
			congrats.setCharacterSize(30);
			congrats.setColor(sf::Color::White);
			congrats.setPosition(WIDTH, 250);
		

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			window.draw(player);
			window.draw(text);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(text5);

			if (winner)
			{
				window.draw(congrats);
			}

			window.display();
			
		}
	return 0;
}
