#ifndef FAMILY_H
#define FAMILY_H

class family
{
public:
    /// @brief Initialize family grid with empty chars
    family();
    /// @brief Destroy all chars in family grid, then destroy family
    ~family();

    /// @brief Output family to the console
    void print();
    /// @brief Replace all chars in Family with ' '
    void clear();
    /// @brief Set a spacific char in the family grid
    /// @param y Row of char
    /// @param x Column of char
    /// @param what Character to place at char location
    void draw(int y, int x, char what);

    /// @brief Return number of columns (width) in family grid
    /// @return Width of family grid
    int get_WIDTH() const { return WIDTH; }
    /// @brief Return number of rows (height) in family grid
    /// @return Height of family grid
    int get_HEIGHT() const { return HEIGHT; }

private:
    /// @brief vertical size of family grid
    static const int HEIGHT;
    /// @brief horizontal size of family grid
    static const int WIDTH;
    /// @brief 2D char structure of family grid
    char **FAMILY;
    /// @brief Character to use to draw boundary of the game
    char borderSymbol;

    /// @brief Construct new family from reference
    /// @param family Reference family to copy
    family(const family &);

    /// @brief Set family equal to reference
    /// @param family Reference family to copy
    /// @return Duplicate of reference family
    family operator=(const family &);
};

#endif