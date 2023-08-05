#ifndef GRID_H
#define GRID_H

#include "Math.h"
#include "Draw.h"

class Grid
{
public:
	Grid(int _w, int _h);
	Vector2i getSize() const { return Vector2i(width, height); }
	Cell getFood() const { return food; };
	void setFoodPos(Vector2i newpos) { food.pos = newpos; }
	void drawFood() const { drawCell(food); }
	void resetFood() { food = Cell(width * 3 / 4, height / 2, Color(RED)); }

private:
	int **grid;
	const int width, height;
	Cell food;
};

#endif