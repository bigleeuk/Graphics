#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);

double x, y;
double xinc, yinc;
static int delay = 1;

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog03: Bouncing pixel");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);

	x = rand() % 50; y = rand() % 50;
	xinc = (double)(rand() % 100) / 500 - 0.1;
	yinc = (double)(rand() % 100) / 500 - 0.1;

}

void display()
{

	glColor3f((GLfloat)x / 50, (GLfloat)y / 50, 0);
	glBegin(GL_POINTS);
	x += xinc;
	y += yinc;

	if (x <= 0 || x >= 50)
	{
		xinc = -xinc;
	}
	if (y <= 0 || y >= 50)
	{
		yinc = -yinc;
	}

	glVertex2f(x, y);
	glEnd();
	glFlush();

}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}