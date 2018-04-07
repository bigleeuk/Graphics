#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>

void init();
void display();
void timer(int t);
void rotate(GLfloat *v, GLfloat d);
void translate(GLfloat *v, GLfloat *t);
double getRadian(int _num);

static int delay = 10;
int theta = 0;

int main(int argc, char* argv[]) {

	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Prog12: Center of rotation");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();
	return 0;

}

void init() {

	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glEnable(GL_DEPTH_TEST);

}

void display() {

	GLfloat t[3] = { 25,25,25 };
	GLfloat v0[3] = { 15,15,35 }, v1[3] = { 35,15,35 }, v2[3] = { 35,35,35 }, v3[3] = { 15,35,35 };
	GLfloat v4[3] = { 40,20,15 }, v5[3] = { 20,20,15 }, v6[3] = { 40,40,15 }, v7[3] = { 20,40,15 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	translate(v0, t); translate(v1, t); translate(v2, t); translate(v3, t);
	translate(v4, t); translate(v5, t); translate(v6, t); translate(v7, t);

	rotate(v0, theta); rotate(v1, theta); rotate(v2, theta); rotate(v3, theta);
	rotate(v4, theta); rotate(v5, theta); rotate(v6, theta); rotate(v7, theta);

	glColor3f(1.0, 0.0, 0.0); glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v1); glVertex3fv(v2); glVertex3fv(v3); glEnd();

	glColor3f(0.0, 1.0, 0.0); glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v1); glVertex3fv(v4); glVertex3fv(v5); glEnd();

	glColor3f(0.0, 0.0, 1.0); glBegin(GL_POLYGON);
	glVertex3fv(v5); glVertex3fv(v4); glVertex3fv(v6); glVertex3fv(v7); glEnd();

	glColor3f(1.0, 1.0, 0.0); glBegin(GL_POLYGON);
	glVertex3fv(v7); glVertex3fv(v6); glVertex3fv(v2); glVertex3fv(v3); glEnd();

	glColor3f(0.0, 1.0, 1.0); glBegin(GL_POLYGON);
	glVertex3fv(v0); glVertex3fv(v5); glVertex3fv(v7); glVertex3fv(v3); glEnd();

	glColor3f(1.0, 0.0, 1.0); glBegin(GL_POLYGON);
	glVertex3fv(v1); glVertex3fv(v4); glVertex3fv(v6); glVertex3fv(v2); glEnd();

	glFlush();
}

void timer(int t)
{
	theta += 1.0;
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

double getRadian(int _num)
{
	return _num*(M_PI / 180);
}

void rotate(GLfloat *v, GLfloat d)
{

	GLfloat x, y, z;
	x = cos(getRadian(theta))*v[0] + sin(getRadian(theta))*v[2];
	y = v[1];
	z = v[0] * -1 * (sin(getRadian(theta))) + v[2] * cos(getRadian(theta));

	v[0] = x, v[1] = y, v[2] = z;
}

void translate(GLfloat *v, GLfloat *t) {
	for (int i = 0; i < 3; i++) {
		v[i] -= t[i];
	}
}