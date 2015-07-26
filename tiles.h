#include <SFML/Graphics.hpp>

class Tile
{
protected:
	unsigned width;
	unsigned length;
	bool wall;
	bool visited;

public:
	// Constructors and destructors
	Tile();
	Tile(unsigned newWidth, unsigned newLength);
	~Tile();

	// Setters & getters
	void setWall(bool state);

	void setVisited(bool state);

	bool isWall();	

	bool isVisited();
	
	// Draw tile
	void draw(int x, int y);
};