#include <iostream>
#include <GL/freeglut.h>

#define BLACK	0,0,0
#define WHITE	1,1,1
#define RED		1,0,0
#define GREEN	0,1,0
#define BLUE	0,0,1

#define COLUMNS			16
#define ROWS			16
#define SCREENWIDTH		glutGet(GLUT_WINDOW_WIDTH)
#define SCREENHEIGHT	glutGet(GLUT_WINDOW_HEIGHT)
#define CELLWIDTH		SCREENWIDTH/COLUMNS
#define CELLHEIGHT		SCREENHEIGHT/ROWS

struct Vector2i
{
	int x, y;
	Vector2i(int _x, int _y) : x(_x), y(_y) {}
};
struct Vector2f
{
	float x, y;
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f(Vector2i _v) : x((float)_v.x), y((float)_v.y) {}
};
struct Color
{
	/// <summary>
	/// The Red, Green, and Blue components of our color, ranging 0-1
	/// </summary>
	float r, g, b;
	/// <summary>
	/// Construct a color from 3 individual floats
	/// </summary>
	/// <param name="_r">Red component</param>
	/// <param name="_g">Green component</param>
	/// <param name="_b">Blue component</param>
	Color(float _r, float _g, float _b) :r(_r), g(_g), b(_b) {}
	/// <summary>
	/// Create a Shade of our color by dividing each component equally
	/// </summary>
	/// <param name="i">Integer to divide our color by</param>
	/// <returns>Shade of color</returns>
	Color operator/(int i) { return Color(r / i, g / i, b / i); }
};

unsigned int FPS;
//const int grid[WIDTH][HEIGHT];

void display(void);
void changeSize(int w, int h);
void timer(int value);
void drawCell(Vector2i pos, Color color);
void drawLine(Vector2i start, Vector2i end, unsigned int lineWidth, Color color);

int main(int argc, char** argv) {
	std::cout << "Hello world!" << std::endl;

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snake");

	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 0.0, 640.0);



	//register callbacks

	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	//enter GLUT event processing loop
	glutMainLoop();

	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawCell(Vector2i(COLUMNS - 1, ROWS - 1), Color(WHITE));

	for (int x = 0; x < COLUMNS; x++)
	{
		drawLine(Vector2i(x, 0), Vector2i(x, ROWS), 2, Color(WHITE) / 10);
	}
	for (int y = 0; y < ROWS; y++)
	{
		drawLine(Vector2i(0, y), Vector2i(COLUMNS, y), 2, Color(WHITE) / 10);
	}

	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	//float ratio = w * 1.0 / h;

	//Reset matrix
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);

	std::cout << "Window dimensions: (" << SCREENWIDTH << ", " << SCREENHEIGHT << ')' << std::endl;
	std::cout << "Cell dimensions: (" << CELLWIDTH << ", " << CELLHEIGHT << ')' << std::endl;
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

void drawCell(Vector2i pos, Color color)
{
	glBegin(GL_QUADS);
	glColor3f(color.r, color.g, color.b);
	glVertex2i(pos.x * CELLWIDTH, pos.y * CELLHEIGHT);
	glVertex2i((pos.x + 1) * CELLWIDTH, pos.y * CELLHEIGHT);
	glVertex2i((pos.x + 1) * CELLWIDTH, (pos.y + 1) * CELLHEIGHT);
	glVertex2i(pos.x * CELLWIDTH, (pos.y + 1) * CELLHEIGHT);
	glEnd();
	//std::cout << "Cell dimensions: (" << pos.x * CELLWIDTH << ", " << pos.y * CELLHEIGHT << ')' << std::endl;
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
