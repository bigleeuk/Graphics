#define _CRT_SECURE_NO_WARNINGS
#define WIND32_LEAN_AND_MEAN
#define SOUND_FILE_NAME  "C:\Users\bigle\source\repos\CCCBAL\CCCBAL.wav"
#define SOUND_FILE_NAME_ENDING "C:\Users\bigle\source\repos\CCCBAL\CCCBAL.wav"
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
#include <time.h>
#include <string.h>
#include <sys/timeb.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm")


DWORD WINAPI ThreadFunc(LPVOID);
void init();
void display();
void collision();
void myMouseMove(GLint x, GLint y);
void keyboard_handler(unsigned char key, int x, int y);
void Dotimer(int t);
void Draw_Square();
void Draw_Circle(float x, float y, float r);
void Sprint(int, int, int, char[]);
void result();
static int delay = 30;

GLint startX = 600;
GLint startY = 600;
GLint endX = 610;
GLint endY = 610;
GLint headX = 615; GLint headY = 615;

boolean flag = false;
boolean firstFlag = false;
boolean resultFlag = false;
int restLife = 3;
char Title[5] = "HODL";
int minutes, second = 0;
char totalTime[30] = "00:00";
char min[30], sec[30];
char result1[50] = "GAME OVER!";
char result2[50] = "";
char result3[50] = "Press the spacebar to restart";
char option[15] = "SPEED: +/-";

// ------------------------------------------------------------------------------------------------
// Define bullet structure
// ------------------------------------------------------------------------------------------------
typedef struct {
	int positionX;
	int positionY;
	int speedX;
	int speedY;
	int directionX;
	int directionY;
}BULL;

BULL bullet[100];
float g_time1 = 0.0;  //별이 중심으로 갈떄까지 시간을 카운트하는 수 (1이되면 멈춤)
float g_time2 = 0.0;  //g_time1이 1이 되면 별들이 중심을 기준으로 회전하도록 값을 줌 (무한증가)
float g_time3 = 0.0;  //g_time1이 1이 되면 중심에서 별이 퍼지도록 카운트 (1이되면 멈춤)

					  // ------------------------------------------------------------------------------------------------
					  // Draw Background functions
					  // ------------------------------------------------------------------------------------------------
void MyIdle(void) {

	g_time1 += 0.005f;  //천천히 중심으로 이동

	if (g_time1 >= 1.0) {  //1이되면 별은 중심
		g_time1 = 1;      //더이상 증가하지 않음
		g_time2 += 0.1f;  //별들의 무한 회전을 하게함
		g_time3 += 0.01f; //별이 퍼지도록 함
		if (g_time3 >= 1.0) g_time3 = 1; //별이 퍼지지만 일정한 범위가 되면 멈춤
	}
	glutPostRedisplay();  //그림을 다시 그림
}

void MyDrawCircle(int cx, int cy, int radius) //midpoint알고리즘에 따라 원을 그림
{

	int x = 0;      //중심에서 이동할 값
	int y = radius;  //y값은 중심으로 부터 떨어진 원의 경계
	int dx = (int)(radius / sqrt(2.0)); //반지름/루트2로 값을 초기화함
	int D = (5 / 4.0 - radius); //첫번째 점의 판별식 F(1,-1/2) -F(0,0) = (5/4.0-radius); 

	glBegin(GL_POINTS);

	while (x < dx) //x는 0이므로 dx(총점의 개수)까지 증가
	{
		x++;
		if (D < 0) //D가 0보다 작을경우 D에 2x+3을 더해줌
		{
			D += 2 * x + 3;

		}
		else if (D >= 0) //D가 0보다 크거나 같은경우 2(x-y)+5를 더해주고 y를 감소
		{
			D += 2 * (x - y) + 5;
			y--;
		}

		//glVertex2i(x + cx, y + cy); /* 한사분면씩 점을 찍어감(8사분면을 통해 원이됨)*/
		//glVertex2i(x + cx, -y + cy);

		//glVertex2i(-x + cx, y + cy);
		//glVertex2i(-x + cx, -y + cy);


		//glVertex2i(y + cx, x + cy);
		//glVertex2i(-y + cx, x + cy);


		//glVertex2i(y + cx, -x + cy);
		//glVertex2i(-y + cx, -x + cy);
	}
	glEnd(); //점그리기 종료

}

// ------------------------------------------------------------------------------------------------
// Event Handler functions
// ------------------------------------------------------------------------------------------------
void myMouseMove(GLint x, GLint y) {
	startX = x;
	startY = y;
	endX = x + 10;
	endY = y + 10;
	headX = x + 10;
	headY = y + 10;
	//printf("%d %d\n ", x, y);
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 32 && !flag) {
		flag = true;
		firstFlag = true;
		resultFlag = false;
		second = 0;
		int termX, termY, termSX, termSY, termDX, termDY;

		//Set randomly bullet feature
		for (int i = 0; i < 100; i++) {
			termX = rand() % 1000;
			termY = rand() % 600;
			termSX = (rand() % 3) + 1;
			termSY = (rand() % 3) + 1;
			termDX = rand() % 2;
			termDY = rand() % 2;

			if (termSX == 0 || termSY == 0)
			{
				termSX = 2;
				termSY = 2;
			}
			bullet[i].positionX = termX;
			bullet[i].positionY = termY;
			bullet[i].speedX = termSX;
			bullet[i].speedY = termSY;
			if (termDX == 0) {
				bullet[i].directionX = 1;
			}
			else {
				bullet[i].directionX = -1;
			}

			if (termDY == 0) {
				bullet[i].directionY = 1;
			}
			else {
				bullet[i].directionY = -1;
			}
		}
	}
	if (key == '+') {
		for (int i = 0; i < 100; i++)
		{
			bullet[i].speedX += 1;
			bullet[i].speedY += 1;
		}
	}
	if (key == '-') {
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].speedX>1 && bullet[i].speedY>1)
			{
				bullet[i].speedX += -1;
				bullet[i].speedY += -1;
			}
		}
	}
	glutPostRedisplay();
}


void Dotimer(int t)
{
	//Move position

	for (int i = 0; i < 100; i++) {
		bullet[i].positionX -= (bullet[i].speedX*bullet[i].directionX);
		bullet[i].positionY -= (bullet[i].speedY*bullet[i].directionY);
	}


	for (int i = 0; i < 100; i++) {
		if (bullet[i].positionY >= 600 || bullet[i].positionY <= 0) {
			bullet[i].directionY = -bullet[i].directionY;
		}
		if (bullet[i].positionX >= 1000 || bullet[i].positionX <= 0) {
			bullet[i].directionX = -bullet[i].directionX;
		}
	}
	//collsion
	for (int i = 0; i < 100; i++)
	{
		if ((startX <= bullet[i].positionX && endX >= bullet[i].positionX) && (startY <= bullet[i].positionY && endY >= bullet[i].positionY))
		{
			flag = false;
			resultFlag = true;
			//printf("ERROR !!!!! and  i:%d \n", i);
		}
	}

	if (flag) {
		collision();
		second = second % 6000;
		if (second < 6000 && second>5998)
			minutes++;
		sprintf(min, "%02d : ", minutes);
		sprintf(sec, "%02d", second / 100);
		strcat(min, sec);
		for (int i = 0; i < strlen(min); i++)
		{
			totalTime[i] = min[i];
		}
	}

	glutPostRedisplay();
	glutTimerFunc(10, Dotimer, 1);
}


// ------------------------------------------------------------------------------------------------
// Thread function
// ------------------------------------------------------------------------------------------------
void collision() {
	HANDLE hThrd;
	DWORD threadId;
	hThrd = CreateThread(NULL, 0, ThreadFunc, (LPVOID)1, 0, &threadId);
	if (hThrd) {
		//printf("Thread launched %d \n", 1);
		//printf("%d %d ::::miniute and second\n", minutes, second);
		CloseHandle(hThrd);

	}

}
DWORD WINAPI ThreadFunc(LPVOID n) {
	
	int i = 0;
	if (resultFlag)
	{
		second = 0;
	}
	else
		second++;
	return 0;
}

// ------------------------------------------------------------------------------------------------
// Draw Polygon and write letter function
// ------------------------------------------------------------------------------------------------
void Draw_Square() {
	glBegin(GL_POLYGON); {
		glColor3f(0.576471,	0.439216,	0.858824); //사각형색 
		glVertex2f(startX, startY); glVertex2f(startX, endY);
		glVertex2f(endX, endY); glVertex2f(endX, startY);
		glVertex2f(headX, headY);
	}
	glEnd();
}

void Draw_Circle(float x, float y, float r) {
	float delta = 2.0*M_PI / 10;
	glBegin(GL_POLYGON);
	glColor3f(0.956863,	0.643137,	0.376471); //총알색 
	for (int i = 0; i < 10; i++) {
		glVertex2f(x + r*cos(delta*i), y + r*sin(delta*i));
	}
	glEnd();
}
void Sprint(int x, int y, int z, char *string) {
	glRasterPos2d(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}
// ------------------------------------------------------------------------------------------------
// Result show functions
// ------------------------------------------------------------------------------------------------
void result()
{

}

// ------------------------------------------------------------------------------------------------
// Init functions
// ------------------------------------------------------------------------------------------------
void init()
{
	ShowCursor(0);
	SetCursorPos(500, 300);
	srand(time(0));
	glClearColor(0.0, 0.0, 0.0, 0.0);// 배경 검은색. 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000.0, 600.0, 0.0); //canvus setting
										 //gluOrtho2D(left, right, bottom, top);
	
}

// ------------------------------------------------------------------------------------------------
// Display functions
// ------------------------------------------------------------------------------------------------
void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); //빨간색으로 삼각형들을 그림.
	if (!firstFlag) {
		char first[40] = "Press the spacebar to start the game";
		Sprint(320, 300, 0, first);
	}

	glMatrixMode(GL_MODELVIEW); // 모델뷰 매트릭스 사용선언
	glLoadIdentity();           // 단위행렬로 초기화
	GLfloat angle = 10.0f;        // 별이 퍼질때 별의 줄을 얼마만큼 돌릴것인가 정함

	float er;                  //원안의 색을 변화하면서 채우기위한 변수
	float cr, cg, cb;            //원안의 색을 저장할 변수
	cr = 1.0;                    //빨간색이 강하도록 지정
	cg = (rand() % 256) / 256.0f;    //다른색은 랜덤(애니메이션시 약간의 색변화가 있도록);
	cb = (rand() % 256) / 256.0f;
	//중심원을 그리는 부분
	glLoadIdentity();                       //행렬을 다시 초기화
	glTranslatef(500 * g_time1, 300.0f, 0.0f);  //별의 위치가 서서히 창의 중심으로 이동하게 함
	glPushMatrix();
	for (er = 0.0; er < g_time3; er += 0.01f) {       //중심에서 안부터 밖으로 원을 그려서 원의 색을 채우게 함

		glColor3f(cr - er, cg - er, cb - er);       //빨간색에서 점점 검은색으로
		MyDrawCircle(0, 0, er * 30);                //midpoint알고리즘으로 원을 그림
	}
	glPopMatrix();

	//왼쪽 별과 폭발로 생성되는 별들과 우주먼지를 그림
	for (; angle <= 360; angle += 30) {             //별을 여러갈래로 생성되게 함        
		for (int i = 0; i < 12; i++) {
			glPushMatrix();                         //Translate가 저장됨
			glColor3f((rand() % 256) / 256.0f + 0.5, (rand() % 256) / 256.0f, (rand() % 256) / 256.0f); //붉은색에 가까운 반짝임효과 
			if (g_time1 >= 1.0f) {                                   //g_time1이 1이 될때, 즉 별이 화면의 중심으로 왔을때
				glRotatef(i*angle + g_time2, 0, 0, 1);                //angle만큼 z축을 중심으로 계속 회전.
				glTranslatef(i*(30 * g_time3), i*(5 * g_time3), 0.0f); //별들의 위치를 이동시킴, g_time3이 1이 될때까지
																	   //우주의 먼지같은 점을 표현 별의 좌측상단, 우측상단, 좌측하단, 우측하단에 표현하여 별과 같이 돔
				glBegin(GL_POINTS);
				glVertex2f(30, 30);
				glVertex2f(-30, 30);
				glVertex2f(-30, -30);
				glVertex2f(30, -30);
				glEnd();
			}
			glPopMatrix(); //다시 삼각형 원 중점(Translate된 곳)으로 돌아가기.
		}
	}
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	Sprint(75, 35, 0, totalTime);
	Sprint(453, 35, 0, Title);
	Sprint(770, 35, 0, option);

	//Redraw Circle

	for (int i = 0; i < 100; i++) {
		glPushMatrix();
		Draw_Circle(bullet[i].positionX, bullet[i].positionY, 3.0);
	}
	glPopMatrix();
	//Redraw Squre
	if (flag)
		Draw_Square();
	if (resultFlag) {

		glColor3f(1.0f, 1.0f, 1.0f);
		Sprint(423, 280, 0, result1); //GAMEOVER
		Sprint(360, 303, 0, result3); //Press the spacebar to restart
		strcpy(result2, totalTime);
		Sprint(453, 325, 0, result2);
	}


	glFlush();
}

// ------------------------------------------------------------------------------------------------
// Main functions
// ------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	PlaySound("galaga10.wav", NULL, SND_ASYNC | SND_LOOP);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(900, 700);
	glutCreateWindow("HODL");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_handler);
	glutPassiveMotionFunc(myMouseMove);
	glutIdleFunc(MyIdle);
	glutTimerFunc(1000, Dotimer, 1);
	glutMainLoop();
	return 0;
}