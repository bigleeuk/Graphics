#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include<math.h>
#include<time.h>
GLfloat Time, Day, Day1 = 0.0;
static  int delay = 10; // milliseconds

void timer(int t){
	Day += (360.0 / (365.0*24.0)) * 10.0;
	if (Day >= 360.0)Day -= 360;
	Day1 += (360.0 / (30.0*24.0)) * 10.0;
	if (Day1 >= 360.0)Day1 -= 360;
	Time += (360.0 / 24.0) * 10.0;
	if (Time >= 360.0)Time -= 360;
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t); // set timer function again
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3); // �¾��� ��
	glutWireSphere(0.2, 20, 16); //�¾� �׸���
	glPushMatrix(); // �¾������ ��ǥ�踦 ���ÿ� Ǫ���Ͽ� ����
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);	//������ �����ֱ�, �¾��� �ִ� ��ġ���� ȸ������
		glRotatef(-23.5, 0.0f, 0.0f, 1.0f);	//������ ���� ����̱� ����
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.7, 0.0, 0.0); // �¾����κ��� 0.7��ŭ ������ �Ÿ�����ġ 
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);			//������ ��ĥ
		glutWireSphere(0.1, 10, 8);	
	glRotatef((GLfloat)-Time, 0.0, 1.0, 0.0);
	glRotatef(-23.5, 0.0f, 0.0f, 1.0f);	//������ ���� ����̱� ����
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef((GLfloat)Day1, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

	
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGl SOLOAR SYSTEM");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(delay, timer, 0);
	glutMainLoop();
	return 0;
}
