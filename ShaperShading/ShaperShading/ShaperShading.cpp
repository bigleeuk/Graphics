#include<math.h>
#include <GL/glut.h>
#include<stdio.h>

int mode = 0;
int degree = 0;
typedef struct Point {
	GLfloat v_tri[3];
}point;
point v[] = {
	{ 0.58,0.58,0.58 },
	{ -0.58,-0.58,0.58 },
	{ 0.58,-0.58,-0.58 },
	{ -0.58,0.58,-0.58 }
};


typedef struct {
	GLfloat position[4];   // position
	GLfloat ambient[4];   // ambient
	GLfloat diffuse[4];   // diffuse
	GLfloat specular[4];   // specular
} Light;

typedef struct {
	GLfloat ambient[4];   // ambient
	GLfloat diffuse[4];   // diffuse
	GLfloat specular[4];   // specular
	GLfloat shininess;    // shininess
} Material;

Light light = {
	{ 0.0, 2.0, 2.0, 1.0 },   // position
	{ 1.0, 1.0, 1.0, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
};

Material mat = {
	{ 0.2, 0.0, 0.0, 1.0 }, // ambient
	{ 1.0, 1.0, 0.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 0.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};
void initTriangle(int);


void triangle(point a, point b, point c, int l)
{
	point v1, v2, v3;
	GLfloat x1, x2, x3;
	if (mode != 2) glShadeModel(GL_FLAT); else glShadeModel(GL_SMOOTH);
	if (mode == 0) glBegin(GL_LINE_LOOP);
	else glBegin(GL_POLYGON);

	glNormal3fv(a.v_tri);
	glVertex3fv(a.v_tri);
	glNormal3fv(b.v_tri);
	glVertex3fv(b.v_tri);
	glNormal3fv(c.v_tri);
	glVertex3fv(c.v_tri);
	glEnd();


	if (l != 0) {
		for (int i = 0; i < 3; i++) {
			v1.v_tri[i] = (a.v_tri[i] + b.v_tri[i]);
			v2.v_tri[i] = (a.v_tri[i] + c.v_tri[i]);
			v3.v_tri[i] = (b.v_tri[i] + c.v_tri[i]);
		}
		x1 = sqrt(v1.v_tri[0] * v1.v_tri[0] + v1.v_tri[1] * v1.v_tri[1] + v1.v_tri[2] * v1.v_tri[2]);
		x2 = sqrt(v2.v_tri[0] * v2.v_tri[0] + v2.v_tri[1] * v2.v_tri[1] + v2.v_tri[2] * v2.v_tri[2]);
		x3 = sqrt(v3.v_tri[0] * v3.v_tri[0] + v3.v_tri[1] * v3.v_tri[1] + v3.v_tri[2] * v3.v_tri[2]);
		for (int i = 0; i < 3; i++) {
			v1.v_tri[i] /= x1; v2.v_tri[i] /= x2; v3.v_tri[i] /= x3;
		}
		triangle(a, v1, v2, l - 1);
		triangle(c, v2, v3, l - 1);
		triangle(b, v3, v1, l - 1);
		triangle(v1, v3, v2, l - 1);
	}
	else return;
}
void initTriangle(int degree)
{

	triangle(v[0], v[1], v[2], degree);
	triangle(v[3], v[2], v[1], degree);
	triangle(v[0], v[3], v[1], degree);
	triangle(v[0], v[2], v[3], degree);

}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.position[0] -= 0.1;
	if (key == 'X') light.position[0] += 0.1;
	if (key == 'y') light.position[1] -= 0.1;
	if (key == 'Y') light.position[1] += 0.1;
	if (key == 'z') light.position[2] -= 0.1;
	if (key == 'Z') light.position[2] += 0.1;

	if (key == 'a') { for (int i = 0; i < 3; i++) light.ambient[i] -= 0.1; }
	if (key == 'A') { for (int i = 0; i < 3; i++) light.ambient[i] += 0.1; }
	if (key == 'd') { for (int i = 0; i < 3; i++) light.diffuse[i] -= 0.1; }
	if (key == 'D') { for (int i = 0; i < 3; i++) light.diffuse[i] += 0.1; }

	if (key == 'm') { mode++; mode = mode % 3; }
	if (key == 'n'&&degree != 0) degree--;
	if (key == 'N') degree++;
}
void spin_cube()
{
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess);
	initTriangle(degree);


	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess);
	glTranslatef(light.position[0], light.position[1], light.position[2]);

	glutSolidSphere(0.1, 10, 10);

	glLightfv(GL_LIGHT0, GL_POSITION, light.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Prog25: Shpere Shading");
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}