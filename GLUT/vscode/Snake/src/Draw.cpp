#include <GL/glut.h>
#include "Draw.h"

void drawCell(Cell c)
{
    glBegin(GL_QUADS);
    glColor3f(c.col.r, c.col.g, c.col.b);
    glVertex2i(c.pos.x * CELLWIDTH, c.pos.y * CELLHEIGHT);
    glVertex2i((c.pos.x + 1) * CELLWIDTH, c.pos.y * CELLHEIGHT);
    glVertex2i((c.pos.x + 1) * CELLWIDTH, (c.pos.y + 1) * CELLHEIGHT);
    glVertex2i(c.pos.x * CELLWIDTH, (c.pos.y + 1) * CELLHEIGHT);
    glEnd();
    // std::cout << "Cell dimensions: (" << pos.x * CELLWIDTH << ", " << pos.y * CELLHEIGHT << ')' << std::endl;
}

void drawLine(Vector2i start, Vector2i end, unsigned int lineWidth, Color color)
{
    glBegin(GL_QUADS);
    glColor3f(color.r, color.g, color.b);
    glVertex2i(start.x * CELLWIDTH - (lineWidth / 2), start.y * CELLHEIGHT - (lineWidth / 2));
    glVertex2i(end.x * CELLWIDTH + (lineWidth / 2), start.y * CELLHEIGHT - (lineWidth / 2));
    glVertex2i(end.x * CELLWIDTH + (lineWidth / 2), end.y * CELLHEIGHT + (lineWidth / 2));
    glVertex2i(start.x * CELLWIDTH - (lineWidth / 2), end.y * CELLHEIGHT + (lineWidth / 2));
    glEnd();

    glEnd();
}