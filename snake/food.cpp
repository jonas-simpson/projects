#include "food.h"
#include <random>

food::food() : symbol('X'), position()
{
    position.x = position.y = -1;
}

void food::set_position(int x, int y)
{
    position.x = x;
    position.y = y;
}

void food::reposition(const family &F)
{
    position.x = std::rand() % F.get_WIDTH();
    position.y = std::rand() % F.get_HEIGHT();
}