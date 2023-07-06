#ifndef FOOD_H
#define FOOD_H

#include "vector.h"
#include "family.h"

class food
{
public:
    /// @brief Construct food with location outside of Family grid
    food();

    /// @brief Set food to precise location in the Family grid
    /// @param x Column to place food
    /// @param y Row to place food
    void set_position(int x, int y);
    /// @brief Set food to random location in the Family grid
    /// @param F Reference family to place food in
    void reposition(const family &F);

    int get_x() const { return position.x; }
    int get_y() const { return position.y; }
    char get_symbol() const { return symbol; }

private:
    vector position;
    char symbol;
};

#endif