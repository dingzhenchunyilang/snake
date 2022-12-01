#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>
#include<mmsystem.h>//多媒体接口的头文件和库
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

#define snake_NUM 500//蛇的最大节数

void initgame();
void Gamedraw();
void snakemove();
void getkey();
void checksnake();

enum dir {
	UP,DOWN,LEFT,RIGHT
};

struct snake {
	int size;//蛇的节数
	int speed;//蛇的速度
	int dir = RIGHT;//蛇的方向
	POINT coor[snake_NUM];//蛇的坐标
}mysnake;
struct food {
	int x;
	int y;
	bool flag;//判断食物是否被吃
	int r;
}food;


int main()
{
	initgame();
	Gamedraw();
	while (1)
	{
		checksnake();
		getkey();
		Gamedraw();
		snakemove();
	}
	return 0;
}


void initgame()
{
	//播放音乐
	mciSendString("open C:\\Users\\86187\\Music\\Re-Logic - Alternate Day alias BGM",0,0,0);
	mciSendString("play BGM repeat",0,0,0);
	initgraph(640, 480);
	//初始化蛇的数据
	mysnake.size = 3;
	mysnake.speed = 10;
	mysnake.dir;
	for (int i = 0; i < mysnake.size; i++)
	{
		mysnake.coor[i].x = 50 - i * 10;
		mysnake.coor[i].y = 10;
	}
	//初始化食物
	srand(time(0));
	food.x = rand() % 640;
	food.y = rand() % 480;

}

void Gamedraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//画蛇
	setfillcolor(GREEN);
	for(int i  = 0;i < mysnake.size ;i++)
	{
		solidcircle(mysnake.coor[i].x, mysnake.coor[i].y, 5/*半径*/);
	}
	//画食物
	setfillcolor(RED);
	solidcircle(food.x, food.y, 6);
	EndBatchDraw();
}

void snakemove()//操控蛇的移动
{
	//让蛇的身体跟着动
	for (int i = mysnake.size - 1; i > 0; i--)
	{
		Sleep(20);
		mysnake.coor[i] = mysnake.coor[i - 1];
	}
	switch (mysnake.dir)//移动蛇头
	{
		case UP:	
			mysnake.coor[0].y -= mysnake.speed;
			Sleep(20);
			break;
		case DOWN:
			mysnake.coor[0].y+= mysnake.speed;
			Sleep(20);
			break;
		case RIGHT:
			mysnake.coor[0].x+= mysnake.speed;
			Sleep(20);
			break;
		case LEFT:
			mysnake.coor[0].x-= mysnake.speed;
			Sleep(20);
			break;
	}
}
void getkey()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (mysnake.dir == DOWN) break;
			mysnake.dir = UP; break;
		case 'd':
		case 'D':
		case 77:
			if (mysnake.dir == LEFT) break;
			mysnake.dir = RIGHT; break;
		case 's':
		case 'S':
		case 80:
			if (mysnake.dir == UP) break;
			mysnake.dir = DOWN; break;
		case 'a':
		case 'A':
		case 75:
			if (mysnake.dir == RIGHT) break;
			mysnake.dir = LEFT; break;
		}
	}
}

void checksnake()
{
	//判断蛇是否撞墙
	if (mysnake.coor[0].x <= 0)
	{
		mysnake.coor[0].x = 640;
	}
	if (mysnake.coor[0].x >= 640)
	{
		mysnake.coor[0].x = 0;
	}
	if (mysnake.coor[0].y >= 480)
	{
		mysnake.coor[0].y = 0;
	}
	if (mysnake.coor[0].y <= 0)
	{
		mysnake.coor[0].y = 480;
	}
	//判断蛇是否吃到食物
	double key = (mysnake.coor[0].x - food.x) * (mysnake.coor[0].x - food.x) + (mysnake.coor[0].y - food.y) * (mysnake.coor[0].y - food.y);
	if (key < 121)
	{
		srand(time(0));
		food.x = rand() % 640;
		food.y = rand() % 480;
		mysnake.size++;
	}
}