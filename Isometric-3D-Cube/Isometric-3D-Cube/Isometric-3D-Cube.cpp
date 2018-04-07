#include <GL/glut.h>
#include <math.h>

void init();
void display();

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
{ -1.0,-1.0,1.0 },{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },
{ 0.0,0.0,1.0 },{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } };

GLubyte indices[] = { 0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4 };

void init()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	glRotatef(35.26, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	/*for (int i = 0; i < 6; i++) {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &indices[4 * i]);
	}*/
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glEnd();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog19: Isometric_3D_cube");
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}

//gluLookAt 카메라의 위치 모델의 위치, 업백터가 보는 방향