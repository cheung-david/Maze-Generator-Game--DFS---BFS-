// Maze Generator - Tiles
// By David Cheung
// Class that consists of the properties of a single maze tile.

#ifndef TILES_H
#define TILES_H

#include <SFML/Graphics.hpp>

class Tile
{
protected:
	unsigned width;
	unsigned length;
	bool wall;
	bool visited;
	int x;
	int y;
	int value;


public:
	// Constructors and destructors
	Tile();
	Tile(unsigned newWidth, unsigned newLength);
	~Tile();

	// Setters & getters
	void setWall(bool state);

	void setVisited(bool state);

	void setX(int newX);
	
	void setY(int newY);

	void setVal(int newVal);

	void setWidth(int newWidth);

	int getX();
	
	int getY();

	int getVal();

	int getWidth();


	bool isWall();	

	bool isVisited();

	
	// Draw tile
	void draw();
};

#endif // TILES_H