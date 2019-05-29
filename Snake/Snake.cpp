
#include <iostream>
#include <graphics.h>
#include <vector>
#include <windows.h>
#include<ctime>
#include <set>

using namespace std;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

const int boardw = 800;
const int boardh = 800;

const int width = 24;
const int height = 24;

int zone[width][height];
int TIM = 100;

int dx[] = { 1,0,-1,0 };
int dy[] = { 0,-1,0,1 };

struct pos
{
	int y;
	int x;
	bool operator == (const pos &a) const
	{
		return a.y == y && a.x == x;
	}
	bool operator < (const pos &a) const
	{
		if (a.y == y)
			return a.x < x;
		return a.y < y;
	}
};

set<pos> s;

int dir = RIGHT;

int dir2 = 0;

int len = 0;

pos snake[500];


pos goal = { -1,-1 };

int flash = 1;

void add(int y, int x)
{
	snake[len++] = { y,x };
}

void point()
{
	srand(unsigned(time(0)));
	int p = rand() % (width * height - len);
	memset(zone, 0, sizeof(zone));
	for (int i = 0; i < len; i++)
		zone[snake[i].y][snake[i].x] = 1;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height ; j++)
		{
			if (zone[i][j] == 0)
			{
				p--;
				if (p == 0)
				{
					goal = { i,j };
					return;
				}
			}
		}
	}
}

void init()
{
	initgraph(boardw, boardh);
	pos tmp;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tmp = { i,j };
		}
	}
	add(10, 0);
	add(10, 1);
	add(10, 2);
	point();
}

void unfill(pos bloc)
{
	clearrectangle(bloc.x * (boardw / width), bloc.y * (boardh / height), (bloc.x + 1) * (boardw / width), (bloc.y + 1) * (boardh / height));
}

void fill(pos bloc)
{
	rectangle(bloc.x * (boardw / width), bloc.y * (boardh / height), (bloc.x + 1) * (boardw / width), (bloc.y + 1) * (boardh / height));
}

void fill1(pos bloc)
{
	auto tmp = getfillcolor();
	setfillcolor(BLACK);
	fillrectangle(bloc.x * (boardw / width), bloc.y * (boardh / height), (bloc.x + 1) * (boardw / width), (bloc.y + 1) * (boardh / height));
	setfillcolor(tmp);
}

void shining()
{
	setlinestyle(PS_NULL);
	if (flash)
		setfillcolor(WHITE);
	else
		setfillcolor(BLACK);
	flash ^= 1;
	fillrectangle(goal.x * (boardw / width) + 1, goal.y * (boardh / height) - 1, (goal.x + 1) * (boardw / width) - 1, (goal.y + 1) * (boardh / height) + 1);
	setlinestyle(PS_SOLID);
}

void paint()
{
	//cleardevice();
	for (int i = 0; i < len; i++)
	{
		fill(snake[i]);
	}
	//fill1(snake[len - 1]);
}

void judge()
{
	for (int i = 0; i < 10; i++)
	{
		if (dir == RIGHT)
		{
			if (KEY_DOWN('W') ^ KEY_DOWN('S'))
			{
				if (KEY_DOWN('S'))
					dir2 = -1;
				else
					dir2 = 1;
			}
		}
		else if (dir == DOWN)
		{
			if (KEY_DOWN('A') ^ KEY_DOWN('D'))
			{
				if (KEY_DOWN('D'))
					dir2 = -1;
				else
					dir2 = 1;
			}
		}
		else if (dir == LEFT)
		{
			if (KEY_DOWN('W') ^ KEY_DOWN('S'))
			{
				if (KEY_DOWN('W'))
					dir2 = -1;
				else
					dir2 = 1;
			}
		}
		else if (dir == UP)
		{
			if (KEY_DOWN('A') ^ KEY_DOWN('D'))
			{
				if (KEY_DOWN('A'))
					dir2 = -1;
				else
					dir2 = 1;
			}
		}
		shining();
		Sleep(TIM/10);
	}
}

void gg()
{
	while (1);
}

void move()
{
	dir = (dir + dir2 + 4) % 4;
	dir2 = 0;
	pos next = { (snake[len - 1].y + dy[dir] + height) % height , (snake[len - 1].x + dx[dir] + width) % width};
	for (int i = 0; i < len; i++)
	{
		if (next == snake[i])
			gg();
	}
	if (next == goal)
	{
		add(goal.y, goal.x);
		fill(goal);
		point();
	}
	else
	{
		pos tmp = snake[0];
		unfill(snake[0]);
		for (int i = 0; i < len - 1; i++)
		{
			snake[i] = snake[i + 1];
			if (abs(snake[i].x - tmp.x) + abs(snake[i].y - tmp.y) == 1)
				fill(snake[i]);
		}
		snake[len - 1] = next;
		fill(next);
	}
}

int main()
{
	printf("简约贪吃蛇Ver 0.99\n");
	printf("by Yin Mingze,16281240@bjtu.edu.cn\n");
	system("pause");
	init();
	while (1)
	{
		judge();
		move();
	}
	return 0;
}

