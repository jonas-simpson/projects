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

	Snake(Vector2i _v, int _length);
	Cell getCell(int i) const;
	Cell getHead() const { return getCell(0); }
	void setDir(MoveDir newDir) { dir = newDir; }
	bool move(const Grid &grid);
	void draw();
	MoveDir processDir(MoveDir newDir);
	Vector2i dirToVector(MoveDir _dir);

private:
	Cell body[100];
	int length;
	MoveDir dir;
	bool shouldGrow;
	// void setShouldGrow(bool _b) { shouldGrow = _b; }
};

#endif