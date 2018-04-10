#include<GL/glut.h>

void init();
void display();
void draw();
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1, 1, 1, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glViewport(0, 0, 250, 250);
	draw();

	glLoadIdentity();
	glViewport(0,250,250,250);/*
	gluLookAt(0,0, 1, 0, 0, 0, 0, 1, 0);*/
	gluLookAt(0, -1, 0, 0, 0, 0, 0, 0, 1);
	draw();
	
	glLoadIdentity();
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
	glViewport(250, 250, 250, 250);
	draw();

	glLoadIdentity();
	gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);
	glViewport(250, 0, 250, 250);
	draw();
	glFlush();

	
}
void draw() {
	glColor3f(0.37, 0.09, 0.82);
	glutWireTeapot(1.0);
	glEnd();
}
int main(int argc, char* argv[]){
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog20: CAD");
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}