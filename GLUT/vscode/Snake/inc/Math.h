#ifndef MATH_H
#define MATH_H

#include <GL/glut.h>

#include "Colors.h"

#define COLUMNS 16
#define ROWS 16
#define SCREENWIDTH glutGet(GLUT_WINDOW_WIDTH)
#define SCREENHEIGHT glutGet(GLUT_WINDOW_HEIGHT)
#define CELLWIDTH SCREENWIDTH / COLUMNS
#define CELLHEIGHT SCREENHEIGHT / ROWS

struct Vector2i
{
	int x, y;
	Vector2i(int _x, int _y) : x(_x), y(_y) {}
	// Vector2i operator()(int _x, int _y) { return Vector2i(_x, _y); }
	Vector2i operator+(Vector2i _v) { return Vector2i(x + _v.x, y + _v.y); }
	Vector2i operator-(Vector2i _v) { return Vector2i(x - _v.x, y - _v.y); }
	bool operator==(Vector2i _v) { return (x == _v.x && y == _v.y); }
	Vector2i operator%(Vector2i _v) { return Vector2i(x % _v.x, y % _v.y); }
	void operator%=(Vector2i _v) { (*this) = (*this) % _v; }
	Vector2i operator*(Vector2i _v) { return Vector2i(x * _v.x, y * _v.y); }
	void operator*=(Vector2i _v) { (*this) = (*this) * _v; }
};
struct Vector2f
{
	float x, y;
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f(Vector2i _v) : x((float)_v.x), y((float)_v.y) {}
};

struct Color
{
	/// @brief The Red, Green, and Blue components of our color, ranging 0-1
	float r, g, b;
	/// @brief Construct a color from 3 individual floats
	/// @param r Red component
	/// @param g Green component
	/// @param b Blue component
	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
	Color(float _rgb) : r(_rgb), g(_rgb), b(_rgb) {}
	/// @brief Create a Shade of our color by dividing each component equally
	/// @param i Integer to divide our color by
	/// @return Shade of color
	Color operator/(int i) { return Color(r / i, g / i, b / i); }
};

struct Cell
{
	Vector2i pos;
	Color col;
	Cell() : Cell(Vector2i(0, 0), Color(BLACK)) {}
	Cell(Vector2i _v, Color _c) : pos(_v), col(_c) {}
	Cell(int _x, int _y, Color _c) : Cell(Vector2i(_x, _y), _c) {}
	Cell(Vector2i _v) : Cell(_v, Color(WHITE)) {}
	Cell(int _x, int _y) : Cell(Vector2i(_x, _y)) {}
	// Cell operator+(Vector2i _v) { return Cell(pos + _v, col); }
};

#endif