// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment (lib,"SDL2")
#pragma comment (lib,"SDL2main")
#pragma comment (lib,"SDL2_image")
#pragma comment (lib,"opengl32.lib")

#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdio.h>
#include <GL\glut.h>
#include<random>
#include<time.h>

#define normalize() srand(time(0))
#define MAX_BULLET  512
#define normalize() srand(time(0))
#define MAX_BULLET  512



bool chk = false;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
typedef struct VECTOR {
	float x, y;
};

VECTOR AddVector(VECTOR a, VECTOR b) {
	VECTOR c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

VECTOR SubVecotr(VECTOR a, VECTOR b) {
	VECTOR c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

void VectorNormalize(VECTOR *a) {
	float Length = sqrt((a->x * a->x) + (a->y * a->y));
	a->x /= (Length * 20.0);
	a->y /= (Length * 20.0);
}

typedef struct Bullet {
	bool IsLive;
	VECTOR Pos;
	VECTOR Des;
	Bullet* prev;
};
typedef struct BulletSystem {
	int Delay;
	Bullet root;
	Bullet tail;
};
BulletSystem BS;
Bullet Bul[MAX_BULLET];


void ProcessBullet(void);
void InitBulletSystem(void) {
	for (int i = 0; i < MAX_BULLET; i++) {
		Bul[i].Pos.x = 0;
		Bul[i].Pos.y = 0;
		Bul[i].Des.x = 0;
		Bul[i].Des.y = 0;
		Bul[i].IsLive = 0;
		Bul[i].prev = NULL;
	}

}
SDL_Surface *background;
SDL_Surface *screen;
SDL_Surface *bullet;
SDL_Surface *texture;
SDL_Rect Position;
SDL_Window *window;
SDL_Renderer *sdlRenderer;
SDL_Renderer * renderer;
SDL_Event event;
bool done = false;
//======================================================================================
//LOAD TEXTURE
//======================================================================================
SDL_Texture *loadTexture(const char *file) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		printf("%s파일을 읽을 수 없습니다.\n", file);
		return NULL;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("텍스쳐를 생성할 수 없습니다.\n");
	}
	SDL_FreeSurface(surface); return texture;
}
//======================================================================================
//Draw Texture
//======================================================================================
void drawTexture(SDL_Renderer *renderer, int x, int y, SDL_Texture *texture) {
	SDL_Rect src, dst;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

//======================================================================================
//LOAD TEXTURE
//======================================================================================
void updateWindow() {
	while (!done) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			}
		}
		ProcessBullet();
		//SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);

	}
}
//======================================================================================
//Main
//======================================================================================
int main(int argc, char *argv[]) {



	BS.Delay = 300;

	BS.root.prev = &BS.tail;
	BS.tail.prev = &BS.root;

	InitBulletSystem();
	//mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	bullet = IMG_Load("./Bullet.bmp");
	background = SDL_LoadBMP("image.bmp");
	SDL_Surface* bmp = SDL_LoadBMP("character.bmp");

	glutInit(&argc, (char**)argv);
	glutInitWindowSize(640, 480);

	SDL_SetColorKey(bullet, SDL_TRUE, SDL_MapRGB(bullet->format, 0xFA, 0x00, 0xFA));
	//SDL_SetColorKey(background, SDL_TRUE, SDL_MapRGB(background->format, 0xFA, 0x00, 0xFA));
	normalize();

	VECTOR Pos, Des;

	Pos.x = 320;
	Pos.y = 240;
	Des.x = 0;
	Des.y = 0;

	Position.x = Pos.x;
	Position.y = Pos.y;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("bullet game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, background);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Rect dstrect = { NULL, NULL, 640, 480 };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	// load background
	drawTexture(renderer, 0, 0, texture);
	SDL_RenderPresent(renderer);
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_Rect dst;

	//처음 위치
	dst.x = 300;
	dst.y = 300;
	screen = SDL_GetWindowSurface(window);



	//--------------------------------------------------------------------------------------
	while (!done) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done= true;
				else if (event.key.keysym.sym == SDLK_LEFT)
					dst.x = dst.x - 10;
				else if (event.key.keysym.sym == SDLK_RIGHT)
					dst.x = dst.x + 10;
				else if (event.key.keysym.sym == SDLK_UP)
					dst.y = dst.y - 10;
				else if (event.key.keysym.sym == SDLK_DOWN)
					dst.y = dst.y + 10;
				SDL_BlitSurface(bmp, NULL, screen, &dst);
				break;
			case SDL_QUIT:
				done = true;
				break;
			}
		} {
			drawTexture(renderer, 0, 0, texture);
			SDL_RenderPresent(renderer);
			//updateWindow();
		}

		//SDL_RenderPresent(renderer);



	}

	SDL_Quit();
	return 0;
}
//======================================================================================
//New bullet
//======================================================================================
void NewBullet() {
	int i;
	// 먼저, live 가 0인 총알을 찾습니다. 이 부분도 링크드 리스트로 처리(관리용이).
	for (i = 0; i < MAX_BULLET; i++) {
		if (!Bul[i].IsLive) break;
	}
	// i 의 위치에 임의의 위치를 지정후 넣음.
	int posx = rand() % 4;
	switch (posx) {
	case 0:
		Bul[i].Pos.x = -16;
		Bul[i].Pos.y = (rand() % 496) - 16;
		break;

	case 1:
		Bul[i].Pos.x = (rand() % 656) - 16;
		Bul[i].Pos.y = -16;
		break;

	case 2:
		Bul[i].Pos.x = 656;
		Bul[i].Pos.y = (rand() % 496) - 16;
		break;

	case 3:
		Bul[i].Pos.x = (rand() % 656) - 16;
		Bul[i].Pos.y = 496;
		break;
	}
	//임시;;; 위치는 0으로 고정.
	Bul[i].Des.x = 320 - Bul[i].Pos.x;
	Bul[i].Des.y = 240 - Bul[i].Pos.y;
	VectorNormalize(&Bul[i].Des);
	Bul[i].IsLive = 1;
	// 링크드 리스트에 등록 합니다. Tail의 바로 앞에 등록
	Bul[i].prev = BS.tail.prev;
	BS.tail.prev = &Bul[i];
}
//======================================================================================
//Process Bullet
//======================================================================================
void ProcessBullet(void) {
	// Delay 값이 0 이면 새로운 총알을 생성
	if (!BS.Delay--) {
		NewBullet();
		BS.Delay = 100;
	}
	// 총알을 이동
	{
		// 총알을 이동 총알 그린다.
		for (Bullet *NowPos = BS.tail.prev, *PrevPos = &BS.tail; NowPos != &BS.root; NowPos = NowPos->prev, PrevPos = PrevPos->prev) {
			// 총알이 화면에서 나가면, 총알을 삭제 처리
			if (NowPos->Des.x > 0) {
				if (NowPos->Des.y > 0) {
					if ((NowPos->Pos.x - 16) > 640 || (NowPos->Pos.y - 16) > 480) {
						NowPos->IsLive = 0;
						PrevPos->prev = NowPos->prev;
						NowPos = NowPos->prev;
					}
				}
				else {
					if ((NowPos->Pos.x - 16) > 640 || (NowPos->Pos.y + 16) < 0) {
						NowPos->IsLive = 0;
						PrevPos->prev = NowPos->prev;
						NowPos = NowPos->prev;
					}

				}

			}
			else
			{
				if (NowPos->Des.y > 0) {

					if ((NowPos->Pos.x + 16) < 0 || (NowPos->Pos.y - 16) > 480) {
						NowPos->IsLive = 0;
						PrevPos->prev = NowPos->prev;
						NowPos = NowPos->prev;
					}
				}
				else {
					if ((NowPos->Pos.x + 16) < 0 || (NowPos->Pos.y + 16) < 0) {
						NowPos->IsLive = 0;
						PrevPos->prev = NowPos->prev;
						NowPos = NowPos->prev;
					}
				}
			}
			NowPos->Pos = AddVector(NowPos->Pos, NowPos->Des);
			Position.x = NowPos->Pos.x - (bullet->w / 2);
			Position.y = NowPos->Pos.y - (bullet->h / 2);
			SDL_BlitSurface(bullet, NULL, screen, &Position);


		}
	}
}

