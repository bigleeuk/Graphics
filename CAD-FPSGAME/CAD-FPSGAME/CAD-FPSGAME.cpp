#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define WIDTH 700
#define HEIGHT 700
#define pi  3.14159265358979323846
void init();
void display();
void draw();
void keyboard();
//void mouseHandler();
GLfloat ro = pi / 24.0;		
static int mouseX, mouseY, PmouseX, PmouseY = 0;
static int ResultX, ResultY = 0;
static int leftbuttonpressed = 0;
static float theta = 0;
GLint angle;
float eye[3] = { 0,0,10 };
float center[3] = {0,0,1};
int down, up = 0;
void init()
{
	printf("===================================init===========================================\n");
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
}
void mousePress(int button, int state, int x, int y) {
	printf("=====================================mouse press===================================\n");
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		mouseX = x; mouseY = y;
		PmouseX = x; PmouseY = y;
		leftbuttonpressed = 1;
		down = 1;
		printf("mouseX and mouseY  : %d %d \n", x, y);
		printf("PmouseX and PmouseY : %d %d \n", PmouseX, PmouseY);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		mouseX = x; mouseY = y;
		ResultX = (PmouseX - mouseX);
		ResultY = (PmouseY - mouseY);
		printf("-------------------------------------------\n");
		printf("Button UP mouseX and mouseY : %d %d \n", x, y);
		printf("Button UP PmouseX and PmouseY : %d %d \n", PmouseX, PmouseY);
		printf("mouse Move ResultX and ResultY : %d %d \n", ResultX, ResultY);
		leftbuttonpressed = 0;
		up = 1;
	}

	//if (up == 1 && down == 1) {
	//	center[0] -= 0.01*(PmouseX - mouseX);
	//	center[1] -= 0.01*(mouseY-PmouseY);

	//	glutPostRedisplay();
	//}
	glutPostRedisplay();
}
void mouseMove(int x, int y) {
	printf("================================mouse move==============================\n");
	if (leftbuttonpressed) {
		printf("the left mouse button is  at (%d , %d)\n", x, y);
		printf("init left mouse button pressed 1 : %d %d \n", PmouseX, PmouseY);
		printf("Result X and Y %d %d\n", ResultX, ResultY);
		center[0] -= 0.01*(PmouseX-(x))/50;
		center[1] -= 0.01*(y-PmouseY)/50;
	}
	glutPostRedisplay();

}
void keyboard(unsigned char key, int x, int y) {
	printf("================================keyboard=========================\n");
	switch (key) {
	case 'w':
		eye[2]--;
		center[2]--;
		break;
	case 's':
		eye[2]++;
		center[2]++;
		break;
	case 'a':
		eye[0]--;
		center[0]--;
		break;
	case 'd':
		eye[0]++;
		center[0]++;
		break;
	default:
		break;

	}
	glutPostRedisplay();
}
void display() {
	printf("========================display Start========================\n");
	ResultX = PmouseX - mouseX;
	ResultY = PmouseY - mouseY;
	int X = ResultX - (WIDTH) / 2;
	printf("result value print  %d \n", angle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0.0, 1.0, 0.0);
	
	draw();
	glFlush();
}
void draw() {
	glPushMatrix();
	glColor3f(0,0.69, 0.74);
	glutWireTeapot(1);
	glColor3f(1, 1, 1);
	glTranslatef(4, 0, 0);
	glutWireSphere(1.0, 50, 50);
	glPopMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-4, 0, 0);
	glutWireTorus(1.0, 0.5, 90, 80);	
	//glEnd();
}
int main(int argc, char* argv[]) {
	printf("=========================main=======================\n");
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Prog20: CAD");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousePress);
	glutMotionFunc(mouseMove);
	init();

	glutMainLoop();

	return 0;
}