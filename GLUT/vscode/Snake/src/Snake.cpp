#include "Snake.h"
#include "Draw.h"

Snake::Snake(Vector2i _v, int _length) : length(_length), dir(RIGHT)
{
	setPos(_v, dir);
}

Cell Snake::getCell(int i) const
{
	if (i < length)
		return body[i];
	else
		return Cell();
}

bool Snake::move(Grid &grid)
{
	// Vector2i moveDir = dirToVector(dir);

	// Check pos + movedir
	// Keep new pos within grid size
	Vector2i newPos = (getHead().pos + dirToVector(dir));
	if (newPos.x < 0)
	{
		newPos.x = grid.getSize().x - 1;
	}
	else if (newPos.y < 0)
	{
		newPos.y = grid.getSize().y - 1;
	}
	newPos %= grid.getSize();

	for (int i = 0; i < length; i++)
	{
		if (newPos == body[i].pos)
		{
			// Snake will hit itself
			return false;
		}
		else if (newPos == grid.getFood().pos)
		{
			// Snake will eat food
			shouldGrow = true;
		}
	}

	// Snake will move one cell
	// Move body first
	if (shouldGrow)
	{
		length++;
		body[length - 1].col = WHITE;
		shouldGrow = false;
		grid.setFoodPos(Vector2i(std::rand() % (grid.getSize().x - 1),
								 std::rand() % (grid.getSize().y - 1)));
	}
	for (int i = length - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	// move head
	body[0] = newPos;

	// draw();

	return true;
}

void Snake::draw() const
{
	for (int i = 0; i < length; i++)
	{
		drawCell(body[i]);
	}
}

Snake::MoveDir Snake::processDir(MoveDir newDir)
{
	// if (((dir == UP || DOWN) && (newDir == UP || DOWN)) ||
	// 	((dir == LEFT || RIGHT) && (newDir == LEFT || RIGHT)))
	// 	return dir;
	// else
	// 	return newDir;
	if (dirToVector(dir) * dirToVector(newDir) == Vector2i(0, 0))
		return newDir;
	else
		return dir;
}

Vector2i Snake::dirToVector(MoveDir _dir)
{
	switch (_dir)
	{
	case UP:
		return Vector2i(0, 1);
	case DOWN:
		return Vector2i(0, -1);
	case LEFT:
		return Vector2i(-1, 0);
	case RIGHT:
		return Vector2i(1, 0);
	}

	// return Vector2i(0);
}

void Snake::setLength(int newLength)
{
	if (newLength == length)
		return;
	else if (newLength < length)
	{
		// if we are shortening snake
		for (int i = length - 1; i > newLength; i--)
		{
			// init out-of-range cells
			body[i] = Cell();
		}
	}
	else
	{
		// if we are lengthening snake
		// get direction of snake tail
		Vector2i relativeDir = body[length - 2].pos - body[length - 1].pos;
		for (int i = length; i < newLength; i++)
		{
			// add cells in relative direction
			body[i] = Cell(body[i - 1].pos + relativeDir);
		}
	}

	length = newLength;
}

void Snake::setPos(Vector2i headPos, MoveDir newDir)
{
	body[0] = Cell(headPos);
	for (int i = 1; i < length; i++)
	{
		body[i] = Cell(body[i - 1].pos - dirToVector(newDir));
	}
}
