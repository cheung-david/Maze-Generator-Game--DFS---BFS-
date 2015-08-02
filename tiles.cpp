// Maze Generator - Tiles
// By David Cheung
// Class that consists of the properties of a single maze tile.

#include "tiles.h"



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

void Tile::setX(int newX)
{
	x = newX;
}

void Tile::setY(int newY)
{
	y = newY;
}

void Tile::setVal(int newVal)
{
	value = newVal;
}

void Tile::setWidth(int newWidth)
{
	width = newWidth;
}

int Tile::getX()
{
	return x;
}

int Tile::getY()
{
	return y;
}

int Tile::getVal()
{ 
	return value; 
}

int Tile::getWidth()
{
	return width;
}

bool Tile::isWall()
{
	return wall;
}

bool Tile::isVisited()
{
	return visited;
}




