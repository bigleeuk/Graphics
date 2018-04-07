#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

void init();
void display();
double getRadian(int num);

double x, y, z;

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Prog09 : Sphere");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void display()
{

	glBegin(GL_TRIANGLE_FAN);

	for (int theta = -180; theta <= 180; theta += 20) {
		glColor3f(fabs(theta) / 180, 0.0, 0.0);
		glVertex3f(0, 0, 0);

		x = sin(getRadian(theta))*cos(getRadian(0));
		y = cos(getRadian(theta))*cos(getRadian(0));
		z = sin(getRadian(0));

		glVertex3f(x, y, z);

		x = sin(getRadian(theta + 20))*cos(getRadian(0));
		y = cos(getRadian(theta + 20))*cos(getRadian(0));
		z = sin(getRadian(0));

		glVertex3f(x, y, z);


	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (int pi = -80; pi <= 80; pi += 20) {

		for (int theta = -180; theta <= 180; theta += 20) {

			glColor3f(fabs(theta) / 180, 0.0, 0.0);
			x = sin(getRadian(theta))*cos(getRadian(pi));
			y = cos(getRadian(theta))*cos(getRadian(pi));
			z = sin(getRadian(pi));

			glVertex3f(x, y, z);
			x = sin(getRadian(theta + 20))*cos(getRadian(pi));
			y = cos(getRadian(theta + 20))*cos(getRadian(pi));
			z = sin(getRadian(pi));

			glVertex3f(x, y, z);
		}
	}

	glEnd();
	glFlush();

}

double getRadian(int num)
{
	return num*(M_PI / 180);
}