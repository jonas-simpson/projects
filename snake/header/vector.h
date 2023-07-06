#ifndef VECTOR_H
#define VECTOR_H

struct vector
{
    int x, y;

    /// @brief Determine whether two vectors occupy the same location
    /// @param other Vector to compare
    /// @return True if vectors are identical, False otherwise
    bool operator==(vector &other) { return (x == other.x && y == other.y); }
};

#endif