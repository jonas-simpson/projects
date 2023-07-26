#ifndef DRAW_H
#define DRAW_H

#include "Math.h"

void drawCell(Cell c);
// void drawCell(Vector2i pos, Color col) { drawCell(Cell(pos, col)); }
void drawLine(Vector2i start, Vector2i end, unsigned int lineWidth, Color color);

#endif