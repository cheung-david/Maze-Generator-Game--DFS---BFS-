#include "tiles.h"

#ifndef TILES_H
#define TILES_H

// Default constructor
Tile::Tile()
{	
	width = 15;
	length = 15;
	visited = false;
	wall = true;
}

Tile::Tile(unsigned newWidth, unsigned newLength)
{
	width = newWidth;
	length = newLength;
	visited = false;
	wall = true;
}

Tile::~Tile()
{
	// Does nothing
}

void Tile::setWall(bool state)
{
	wall = state;
}

void Tile::setVisited(bool state)
{
	visited = state;
}

bool Tile::isWall()
{
	return wall;
}

bool Tile::isVisited()
{
	return visited;
}

void Tile::draw(int x, int y)
{
	sf::RectangleShape tile(sf::Vector2f(width, length));
	if (isWall())
	{
		tile.setFillColor(sf::Color(255, 255, 255));
		tile.setPosition(x, y);
	}
	else
	{
		tile.setFillColor(sf::Color(0, 0, 0));
		tile.setPosition(x, y);
	}
}

#endif
