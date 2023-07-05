#ifndef CLASS_H
#define CLASS_H

#include "vector.h"
#include "food.h"
#include "family.h"

class snake
{
public:
    /// @brief Initialize variables and set Head position
    /// @param x Head position X
    /// @param y Head position Y
    snake(int x, int y);
    /// @brief Check if Head is currently sharing a Family location with Food
    bool check_food(const food &food);
    /// @brief Check for and store keystrokes
    void get_input(const family &F);
    /// @brief Update snake location in Family
    void move(const family &F);
    /// @brief Push snake characters to Family draw call
    void draw(family &F);
    int get_x() const { return head.x; }
    int get_y() const { return head.y; }
    // char get_symbol() const { return symbol; }

private:
    enum direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } currentDirection;

    // char symbol, head_symbol;
    /// @brief Initialize 100 snake segments
    vector position[100];
    /// @brief Head of the snake
    vector &head;
    /// @brief Number of Family units to move in one update
    int speed;
    /// @brief Number of snake segments, including Head
    int size;
    bool can_turn;

    /// @brief Determine character used at location in Snake
    /// @param segment Location to check
    /// @return Char used at location
    char getSymbolFromSegment(int segment);
    /// @brief Check location against body segments for self-collisions
    /// @param target Location to check, usually the Head
    /// @return Whether location overlaps with Snake body
    bool checkSelf(vector target);
};

#endif