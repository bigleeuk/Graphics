#include <GL/glut.h>

void init();
void display();
void DrawTriangle(GLfloat* a, GLfloat* b, GLfloat* c, int t);

GLfloat a[2] = { 0,0 };
GLfloat b[2] = { 25,50 };
GLfloat c[2] = { 50,0 };

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog04: Recursive Triangles");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f((GLfloat)1, (GLfloat)0, (GLfloat)0);

}

void display()
{
	glBegin(GL_TRIANGLES);
	DrawTriangle(a, b, c, 5);

	glEnd();
	glFlush();

}

void DrawTriangle(GLfloat * a, GLfloat * b, GLfloat * c, int t)
{
	GLfloat aPrime[2], bPrime[2], cPrime[2];
	if (t > 0) {
		aPrime[0] = (a[0] + b[0]) / 2; 	aPrime[1] = (a[1] + b[1]) / 2;
		bPrime[0] = (b[0] + c[0]) / 2; 	bPrime[1] = (b[1] + c[1]) / 2;
		cPrime[0] = (a[0] + c[0]) / 2; 	cPrime[1] = (a[1] + c[1]) / 2;

		DrawTriangle(aPrime, b, bPrime, t - 1);
		DrawTriangle(a, aPrime, cPrime, t - 1);
		DrawTriangle(cPrime, bPrime, c, t - 1);
	}
	else {
		glVertex2fv(a); glVertex2fv(b); glVertex2fv(c);
	}

}