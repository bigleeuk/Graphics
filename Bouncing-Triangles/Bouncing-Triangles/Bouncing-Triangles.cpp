#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
void timer(int t);

double x[3], y[3];
double xinc[3], yinc[3];

static int delay = 1;

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog06: Bouncing triangle");
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

	for (int i = 0; i < 3; i++) {
		x[i] = rand() % 50; y[i] = rand() % 50;
		xinc[i] = (double)(rand() % 100) / 500 - 0.1;
		yinc[i] = (double)(rand() % 100) / 500 - 0.1;
	}
}

void display()
{

	glColor3f((GLfloat)x[0] / 50, (GLfloat)y[0] / 50, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 3; i++) {

		x[i] += xinc[i];
		y[i] += yinc[i];
		if (x[i] <= 0 || x[i] >= 50)
		{
			xinc[i] = -xinc[i];
		}
		if (y[i] <= 0 || y[i] >= 50)
		{
			yinc[i] = -yinc[i];
		}
	}

	for (int i = 0; i < 3; i++) {
		glVertex2f(x[i], y[i]);
	}

	glEnd();
	glFlush();

}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}