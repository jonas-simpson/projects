#include "family.h"
#include <iostream>

using std::cout;
using std::endl;
using std::flush;

// Define Family dimensions
const int family::HEIGHT = 23;
const int family::WIDTH = 23;

family::family() : borderSymbol('#')
{
    FAMILY = new char *[HEIGHT];
    for (int column = 0; column < HEIGHT; ++column)
    {
        FAMILY[column] = new char[WIDTH];
    }

    for (int i = 0; i < HEIGHT; ++i)
    {
        draw(i, 0, '#');
        draw(i, WIDTH - 1, '#');
    }
    for (int i = 0; i < WIDTH; ++i)
    {
        draw(0, i, '#');
        draw(HEIGHT - 1, i, '#');
    }
}

family::~family()
{
    for (int column = 0; column < HEIGHT; ++column)
    {
        delete[] FAMILY[column];
    }
    delete[] FAMILY;
}

void family::print()
{
    for (int column = 0; column < HEIGHT; ++column)
    {
        for (int row = 0; row < WIDTH; ++row)
        {
            cout << FAMILY[column][row] << flush;
        }
        cout << endl;
    }
}

void family::clear()
{
    for (int column = 1; column < HEIGHT - 1; ++column)
    {
        for (int row = 1; row < WIDTH - 1; ++row)
        {
            FAMILY[column][row] = ' ';
        }
    }
}

void family::draw(int y, int x, char what)
{
    FAMILY[y][x] = what;
}