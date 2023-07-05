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
    for (int column = 0; column < HEIGHT; ++column)
    {
        for (int row = 0; row < WIDTH; ++row)
        {
            FAMILY[column][row] = ' ';
        }
    }
}

void family::draw(int y, int x, char what)
{
    FAMILY[y][x] = what;
}