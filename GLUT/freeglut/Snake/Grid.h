#ifndef GRID_H
#define GRID_H

#include "Math.h"

class Grid
{
public:
	Grid(int _w, int _h);
	Vector2i getSize() const { return Vector2i(width, height); }
	Cell getFood() const { return food; };
private:
	const int** grid;
	const int width, height;
	Cell food;
};

#endif GRID_H