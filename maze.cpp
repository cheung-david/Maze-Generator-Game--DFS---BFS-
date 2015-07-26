#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Maze Game");
	sf::RectangleShape player(sf::Vector2f(10, 10));
	player.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}