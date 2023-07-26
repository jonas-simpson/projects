#include "Snake.h"

Snake::Snake(Vector2i _v) : length(1), dir(RIGHT)
{
	body[0] = Cell(_v);
}

bool Snake::move(const Grid& grid)
{
	Vector2i moveDir(0, 0);

	switch (dir)
	{
	case UP:
		moveDir.y = 1;
		break;
	case DOWN:
		moveDir.y = -1;
		break;
	case RIGHT:
		moveDir.x = 1;
		break;
	case LEFT:
		moveDir.x = -1;
		break;
	}

	//Check pos + movedir
	//Keep new pos within grid size
	Vector2i newPos = (getHead().pos + moveDir) % grid.getSize();
	for (int i = 0; i < length; i++)
	{
		if (newPos == body[i].pos)
		{
			//Snake will hit itself
			return false;
		}
		else if (newPos == grid.getFood().pos)
		{
			//Snake will eat food
		}
		else
		{
			//Snake will move one cell
			//Move body first
			for (int i = length - 1; i > 0; i--)
			{
				body[i] = body[i - 1];
			}
			//move head
			body[0] = newPos;
		}

		draw();
	}

	//if available, move to new pos


	return true;
}
