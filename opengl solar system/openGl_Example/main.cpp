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
	glColor3f(1.0, 0.3, 0.3); // 태양의 색
	glutWireSphere(0.2, 20, 16); //태양 그리기
	glPushMatrix(); // 태양기준의 좌표계를 스택에 푸시하여 저장
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);	//지구의 공전주기, 태양이 있는 위치에서 회전지정
		glRotatef(-23.5, 0.0f, 0.0f, 1.0f);	//지구의 축을 기울이기 위함
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.7, 0.0, 0.0); // 태양으로부터 0.7만큼 떨어진 거리에위치 
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);			//지구의 색칠
		glutWireSphere(0.1, 10, 8);	
	glRotatef((GLfloat)-Time, 0.0, 1.0, 0.0);
	glRotatef(-23.5, 0.0f, 0.0f, 1.0f);	//지구의 축을 기울이기 위함
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
