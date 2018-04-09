#include <GL/glut.h>
#include <math.h>

void init();
void display();
void polygon(int a, int b, int c, int d);
void spin_cube();
GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
{ -1.0,-1.0,1.0 },{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },
{ 0.0,0.0,1.0 },{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } };
static GLfloat theta = 0.0;
static float axis[3] = { 0.1,0.1,0.1 };
static float view[3] = { 3,3,3 };
static int change = 0;
static float scale=1;
static int ortho = 0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//gluPerspective(85.0, 1.0, 2.0, 20.0);
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	//glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(view[0], view[1], view[2], 0 , 0, 0 , 0, 1, 0 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (change==1) {
		glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
		//gluPerspective(85.0, 1.0, 2.0, 20.0);
		glScalef(scale, scale, scale);
		polygon(0, 3, 2, 1);
		polygon(2, 3, 7, 6);
		polygon(0, 4, 7, 3);
		polygon(1, 2, 6, 5);
		polygon(4, 5, 6, 7);
		polygon(0, 1, 5, 4);
		
	}

	else if(change==0) {
		gluPerspective(85.0, 1.0, 2.0, 20.0);
		glScalef(scale, scale, scale);
		polygon(0, 3, 2, 1);
		polygon(2, 3, 7, 6);
		polygon(0, 4, 7, 3);
		polygon(1, 2, 6, 5);
		polygon(4, 5, 6, 7);
		polygon(0, 1, 5, 4);
		
	}
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
	
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'x':
		view[0] = view[0] -0.1;
		break;
	case 'X':
		view[0] = view[0] + 0.1;
		break;
	case 'y':
		view[1] = view[1] - 0.1;
		break;
	case 'Y':
		view[1] = view[1] + 0.1;
		break;
	case 'z':
		view[2] = view[2] - 0.1;
		break;
	case 'Z':
		view[2] = view[2] + 0.1;
		break;
	case 'p':
		if (change == 0) {
			scale = 0.4;
			change = 1;
		}
		else if (change == 1) {
			scale = 1.0;
			change = 0;
		}
		break;
	default:
		break;
	}
}

void spin_cube()
{
	
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Prog16: Smooth rendering");
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);


	glutIdleFunc(spin_cube);
	init();
	glutMainLoop();

	return 0;
}