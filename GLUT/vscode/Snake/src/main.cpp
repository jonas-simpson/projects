#include <iostream>
#include <GL/glut.h>

#include "Math.h"
#include "Colors.h"
#include "Draw.h"
#include "Grid.h"
#include "Snake.h"

unsigned int FPS;
// const int grid[COLUMNS][ROWS];

void display(void);
void changeSize(int w, int h);
void timer(int value);
void keys(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void reset();

bool isAlive = true;
Vector2i snakeStartPos = Vector2i(COLUMNS / 4, ROWS / 2);
int snakeStartLength = 4;

Grid myGrid(COLUMNS, ROWS);
Snake mySnake(snakeStartPos, snakeStartLength);
Snake::MoveDir latestDir = Snake::MoveDir::RIGHT;

int main(int argc, char **argv)
{
	std::cout << "Hello world!" << std::endl;

	glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snake");

	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 0.0, 640.0);

	// register callbacks
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);

	// enter GLUT event processing loop
	glutMainLoop();

	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// drawCell(Vector2i(COLUMNS - 1, ROWS - 1), Color(WHITE));

	for (int x = 0; x < COLUMNS; x++)
	{
		drawLine(Vector2i(x, 0), Vector2i(x, ROWS), 2, Color(WHITE) / 10);
	}
	for (int y = 0; y < ROWS; y++)
	{
		drawLine(Vector2i(0, y), Vector2i(COLUMNS, y), 2, Color(WHITE) / 10);
	}

	mySnake.setDir(mySnake.processDir(latestDir));
	isAlive = mySnake.move(myGrid);
	if (!isAlive)
	{
		// GAME OVER
		std::cout << "YEEEEOWCH!" << std::endl;
		std::cout << "Press any key to reset ..." << std::endl;
	}

	myGrid.drawFood();
	mySnake.draw();

	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	// float ratio = w * 1.0 / h;

	// Reset matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);

	std::cout << "Window dimensions: (" << SCREENWIDTH << ", " << SCREENHEIGHT << ')' << std::endl;
	std::cout << "Cell dimensions: (" << CELLWIDTH << ", " << CELLHEIGHT << ')' << std::endl;
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(256, timer, 0);
}

void keys(unsigned char key, int x, int y)
{
	if (isAlive)
		return;
	reset();
}

void specialKeys(int key, int x, int y)
{
	if (isAlive)
	{
		switch (key)
		{
		case (GLUT_KEY_UP):
			latestDir = Snake::UP;
			break;
		case (GLUT_KEY_DOWN):
			latestDir = Snake::DOWN;
			break;
		case (GLUT_KEY_LEFT):
			latestDir = Snake::LEFT;
			break;
		case (GLUT_KEY_RIGHT):
			latestDir = Snake::RIGHT;
			break;
		}
		return;
	}
	reset();
}

void reset()
{
	if (isAlive)
		return;

	isAlive = true;
	mySnake.setPos(snakeStartPos, Snake::MoveDir::RIGHT);
	mySnake.setLength(snakeStartLength);
	myGrid.resetFood();
	latestDir = Snake::MoveDir::RIGHT;
}