#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include <string.h>

#define UP 30000
#define DOWN 30001
#define RIGHT 30002
#define LEFT 30003

#define START_X 5    
#define START_Y 5
#define HEIGHT 20
#define WIDTH 25

#define MONSTER1  30006
#define MONSTER2  30008
#define ITEM 30009
#define PLAYER  30007

//mapData
int map[HEIGHT][WIDTH] = { 0, };
int monstermap1[HEIGHT][WIDTH] = { 0, };
int monstermap2[HEIGHT][WIDTH] = { 0, };
char monster = 1;
char player = 2;
char wall = 178;

int i = 0;
int j = 0;

int playerX = 0;
int playerY = 0;
int beforePosX = 0;
int beforePosY = 0;
int monster1X = 0;
int monster1Y = 0;
int monster2X = 0;
int monster2Y = 0;

char input = 0;
int isPlay = 1;

//파일 입출력
char path[256] = "c:\\tc30\\bin\\";
char isloadfile = 0;
char filename[30];
char fullfilename[256];
char *file[3] = {"STAGE1.TXT", "STAGE2.TXT", "STAGE3.TXT"};
FILE *fp;

int stagenum = 0;
int monstercounter = 0;

void SeacrchPlayer()
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == PLAYER) {
				gotoxy(START_X + j, START_Y + i);
				printf("%c", player);
				playerX = START_X + j;
				playerY = START_Y + i;
				return;
			}
		}
	}
}

void SeacrchMonster()
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == MONSTER1)
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", monster);
				monster1X = START_X + j;
				monster1Y = START_Y + i;
			}
			else if(map[i][j] == MONSTER2) 
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", monster);
				monster2X = START_X + j;
				monster2Y = START_Y + i;
			}
		}
	}
}

void Readmap()
{
	int tmp[1000];
	char ch_1;
	int total_ch = 0;
	int num = 0;

	strcpy(fullfilename, path);
	strcat(fullfilename, file[stagenum]);
	isloadfile = 1;

	fp = fopen(fullfilename, "r");

	if (fp == NULL)
	{
		printf("file is NULL");
		getch();
		return;
	}
	else
	{
		while (1)
		{
			ch_1 = fgetc(fp);
			if (ch_1 == EOF) {
				break;
			}
			if (ch_1 != '\n') {
				tmp[total_ch++] = ch_1;
			}
		}

		for (i = 0; i < HEIGHT; i++)
		{
			for (j = 0; j < WIDTH; j++)
			{
				if (tmp[num] == 45)
				{
					map[i][j] = 1;
					num += 2;
				}
				else if (tmp[num] == 109)
				{
					if (monstercounter == 0) {
						map[i][j] = MONSTER1;
						monstercounter++;
					}
					else {
						map[i][j] = MONSTER2;
					}	
					num++;
				}
				else if (tmp[num] == 112)
				{
					map[i][j] = PLAYER;
					num++;
				}
				else if (tmp[num] == 105)
				{
					map[i][j] = ITEM;
					num++;
				}
				else
				{
					map[i][j] = tmp[num++] - 48;
				}
			}
		}
	}
}

void DrawMap()
{	
   for (i = 0; i < HEIGHT; i++)
   {
      for (j = 0; j < WIDTH; j++)
      {
         if (map[i][j] == 1) {
			 map[i][j] = -1;
            gotoxy(START_X + j, START_Y + i);
            printf("%c", 178);
		 }
		 else if(map[i][j] == ITEM) {
			 gotoxy(START_X + j, START_Y + i);
			 printf("%c", 3);
		 }
      }
      printf("\n");
   }
}

void main()
{
    clrscr();
	Readmap();
	DrawMap();
    SeacrchPlayer();
	SeacrchMonster();

    while (isPlay)
	{
		if (kbhit())
		{
			input = getch();	
		}
		switch (input)
		{
		case 'a':
			playerX--;
			break;

		case 'd':
			playerX++;
			break;

		case 'w':
			playerY--;
			break;

		case's':
			playerY++;
			break;

		case 'q':
			return;

		}
        if (map[playerY - START_Y][playerX - START_X] == -1)
        {
            playerX = beforePosX;
            playerY = beforePosY;
        }
        gotoxy(beforePosX, beforePosY);
        printf(" ");
        gotoxy(playerX, playerY);
        printf("%c", player);
        beforePosX = playerX;
        beforePosY = playerY;
        delay(200);
	}
	delay(200);
}