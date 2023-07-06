#include "snake.h"
#include "symbol.h"
#include <windows.h>

snake::snake(int x, int y) :             /*symbol('#'), head_symbol('@'),*/
                             position(), /*speed(1),*/
                             size(4), currentDirection(RIGHT),
                             head(position[0]), can_turn(true)
{
    position[0].x = x;
    position[0].y = y;
}

bool snake::check_food(const food &food)
{
    if (food.get_x() == head.x && food.get_y() == head.y)
    {
        size += 1;
        return true;
    }

    return false;
}

void snake::get_input(const family &F)
{
    if (GetAsyncKeyState(VK_UP) && currentDirection != DOWN)
    {
        currentDirection = UP;
    }
    if (GetAsyncKeyState(VK_DOWN) && currentDirection != UP)
    {
        currentDirection = DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT) && currentDirection != RIGHT)
    {
        currentDirection = LEFT;
    }
    if (GetAsyncKeyState(VK_RIGHT) && currentDirection != LEFT)
    {
        currentDirection = RIGHT;
    }
}

void snake::move(const family &F)
{
    vector next = {0, 0};
    switch (currentDirection)
    {
    case UP:
        next.y = -1;
        break;
    case DOWN:
        next.y = 1;
        break;
    case LEFT:
        next.x = -1;
        break;
    case RIGHT:
        next.x = 1;
    }

    for (int s = size - 1; s > 0; --s)
    {
        position[s] = position[s - 1];
    }

    head.x += next.x;
    head.y += next.y;

    if (head.x < 0 || head.y < 0 ||
        head.x >= F.get_WIDTH() || head.y >= F.get_HEIGHT() ||
        checkSelf(head))
    {
        throw "DEAD!";
    }
}

char snake::getSymbolFromSegment(int segment)
{
    switch (segment)
    {
    // Mouth
    case 0:
        switch (currentDirection)
        {
        case LEFT:
            return MOUTH_LEFT;
        case RIGHT:
            return MOUTH_RIGHT;
        case UP:
            return MOUTH_UP;
        case DOWN:
            return MOUTH_DOWN;
        }
    // Eyes
    case 1:
        switch (currentDirection)
        {
        case LEFT:
            return EYES_LEFT;
        case RIGHT:
            return EYES_RIGHT;
        case UP:
            return EYES_UP;
        case DOWN:
            return EYES_DOWN;
        }
    // Body
    default:
        return SNAKE_BODY;
    }
}

void snake::draw(family &F)
{
    for (int s = 0; s < size; ++s)
    {
        F.draw(position[s].y, position[s].x, getSymbolFromSegment(s));
    }
}

bool snake::checkSelf(vector target)
{
    for (int s = 4; s < size; s++)
    {
        // If Snake is long enough, check to see if it ran into itself
        if (target == position[s])
        {
            return true;
        }
    }

    return false;
}