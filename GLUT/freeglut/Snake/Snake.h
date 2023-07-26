#include "Math.h"
#include "Grid.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
	enum MoveDir
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Snake(Vector2i _v);
	Cell getCell(int i) const;
	Cell getHead() const { return getCell(0); }
	bool move(const Grid& grid);
	void grow();
	void draw();

private:
	Cell body[100];
	int length;
	MoveDir dir;
};

#endif