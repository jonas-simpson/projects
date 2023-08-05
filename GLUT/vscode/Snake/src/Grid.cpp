#include "Grid.h"
#include "Colors.h"
#include "Math.h"

Grid::Grid(int _w, int _h) : width(_w), height(_h)
{
	grid = new int *[width];
	for (int x = 0; x < width; x++)
	{
		grid[x] = new int[height];
	}

	resetFood();
}
