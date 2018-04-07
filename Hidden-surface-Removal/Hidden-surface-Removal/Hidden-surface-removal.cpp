#include <GL/glut.h>

void init();
void display();

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Prog08: hidden surface removal");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void display()
{
	glColor3f(1.0, 0.0, 0.0); //1
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();

	glColor3f(0.0, 0.0, 1.0); //2
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(40, 20, 15); glVertex3f(20, 20, 15);
	glEnd();

	glColor3f(1.0, 1.0, 0.0); //3
	glBegin(GL_POLYGON);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); glVertex3f(40, 40, 15); glVertex3f(20, 40, 15);
	glEnd();

	glColor3f(0.0, 1.0, 1.0); //4
	glBegin(GL_POLYGON);
	glVertex3f(20, 40, 15); glVertex3f(40, 40, 15); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();

	glColor3f(1.0, 0.0, 1.0); //5
	glBegin(GL_POLYGON);
	glVertex3f(35, 35, 35); glVertex3f(40, 40, 15); glVertex3f(40, 20, 15); glVertex3f(35, 15, 35);
	glEnd();

	glColor3f(0.0, 1.0, 0.0); //6
	glBegin(GL_POLYGON);
	glVertex3f(20, 40, 15); glVertex3f(20, 20, 15); glVertex3f(15, 15, 35); glVertex3f(15, 35, 35);
	glEnd();

	glFlush();
}