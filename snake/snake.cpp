#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>
#include<mmsystem.h>//��ý��ӿڵ�ͷ�ļ��Ϳ�
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

#define snake_NUM 500//�ߵ�������

void initgame();
void Gamedraw();
void snakemove();
void getkey();
void checksnake();

enum dir {
	UP,DOWN,LEFT,RIGHT
};

struct snake {
	int size;//�ߵĽ���
	int speed;//�ߵ��ٶ�
	int dir = RIGHT;//�ߵķ���
	POINT coor[snake_NUM];//�ߵ�����
}mysnake;
struct food {
	int x;
	int y;
	bool flag;//�ж�ʳ���Ƿ񱻳�
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
	//��������
	mciSendString("open C:\\Users\\86187\\Music\\Re-Logic - Alternate Day alias BGM",0,0,0);
	mciSendString("play BGM repeat",0,0,0);
	initgraph(640, 480);
	//��ʼ���ߵ�����
	mysnake.size = 3;
	mysnake.speed = 10;
	mysnake.dir;
	for (int i = 0; i < mysnake.size; i++)
	{
		mysnake.coor[i].x = 50 - i * 10;
		mysnake.coor[i].y = 10;
	}
	//��ʼ��ʳ��
	srand(time(0));
	food.x = rand() % 640;
	food.y = rand() % 480;

}

void Gamedraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//����
	setfillcolor(GREEN);
	for(int i  = 0;i < mysnake.size ;i++)
	{
		solidcircle(mysnake.coor[i].x, mysnake.coor[i].y, 5/*�뾶*/);
	}
	//��ʳ��
	setfillcolor(RED);
	solidcircle(food.x, food.y, 6);
	EndBatchDraw();
}

void snakemove()//�ٿ��ߵ��ƶ�
{
	//���ߵ�������Ŷ�
	for (int i = mysnake.size - 1; i > 0; i--)
	{
		Sleep(20);
		mysnake.coor[i] = mysnake.coor[i - 1];
	}
	switch (mysnake.dir)//�ƶ���ͷ
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
	//�ж����Ƿ�ײǽ
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
	//�ж����Ƿ�Ե�ʳ��
	double key = (mysnake.coor[0].x - food.x) * (mysnake.coor[0].x - food.x) + (mysnake.coor[0].y - food.y) * (mysnake.coor[0].y - food.y);
	if (key < 121)
	{
		srand(time(0));
		food.x = rand() % 640;
		food.y = rand() % 480;
		mysnake.size++;
	}
}