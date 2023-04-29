#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<conio.h>
#include <string.h>

#define MONSTER 30006
#define MONSTER2 30008
#define PLAYER 30007
#define ITEM 30009
#define START_X 5
#define START_Y 5
#define HEIGHT 20
#define WIDTH 25

int state = -1;
int isedit = 1;
int map[HEIGHT][WIDTH] = { 0, };
char key = -1;
char tmpch = -1;
int xpos = 0;
int ypos = 0;
char menu = -1;

char filename[30];
char path[256] = "c:\\tc30\\bin\\";
char fullfilename[256];
int isloadfile = 0;
FILE* fp;

int i =0;
int j =0;

void Createmap()
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++) {
			
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
			{
				map[i][j] = -1;
			}
			else
			{
				map[i][j] = 0;
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

	printf("Input filename");
	scanf("%s", filename);

	strcpy(fullfilename, path);
	strcat(fullfilename, filename);
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
			for ( j = 0; j < WIDTH; j++)
			{
				if (tmp[num] == 45) 
				{				
					map[i][j] = -1;
					num += 2;
				}
				else if (tmp[num] == 109) 
				{
					map[i][j] = MONSTER;
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
					map[i][j] = tmp[num++]-48;
				}
			}
		}
	}
}



void Freemap()
{
	for (i = 0; i < HEIGHT; i++)
	{
		free(map[i]);
	}
	free(map);
}

void Editmap()
{
	
}

void Inputkey()
{
	gotoxy(START_X + xpos, START_Y + ypos);
	if (kbhit())
	{
		tmpch = getch();
		if (tmpch == 32 || tmpch >=64)
		{
			key = tmpch;
		}
		else if( tmpch >= 48 || tmpch < 55)
		{
			menu = tmpch;
			gotoxy(5, 3);
			printf("input menu : %c", menu);
		}

		switch (key)
		{
		case 'a':
		case 'A':
			if (xpos - 1 >0)
			{
				xpos--;
			}
			break;

		case 'd':
		case 'D':
			if (xpos + 1  < WIDTH - 1)
			{
				xpos++;
			}
			break;

		case 'w':
		case 'W':
			if (ypos - 1  > 0)
			{
				ypos--;
			}
			break;

		case 's':
		case 'S':
			if (ypos + 1  < HEIGHT-1)
			{
				ypos++;
			}
			break;

		case 32:
			Editmap();
			break;

		case 'q':
		case 'Q':
			Freemap();
			isedit = 0;
			break;
		}
		gotoxy(START_X + xpos, START_Y + ypos);
	}
}

void Drawmap()
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == -1) 
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", 178);
			}
			else if (map[i][j] == MONSTER)
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", 1);
			}
			else if (map[i][j] == PLAYER)
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", 2);
			}
			else if (map[i][j] == ITEM)
			{
				gotoxy(START_X + j, START_Y + i);
				printf("%c", 3);
			}
		}
		printf("\n");
	}
	xpos = WIDTH / 2;
	ypos = HEIGHT / 2;
	gotoxy(START_X+ xpos, START_Y + ypos);
}
void Drawmap2()
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			gotoxy(START_X + j + WIDTH + 5, START_Y + i);
			printf("%d",map[i][j]);
		}
		printf("\n");
	}
}


void main()
{
    clrscr();

  	printf(" 1: Create map  2 : Open map");
	scanf("%d", &state);

	if (state == 1)
	{
		Createmap();
	}
	else
	{
		Readmap();
	}
    
	clrscr();
	Drawmap2();
	Drawmap();

	while (isedit)
	{
		Inputkey();
	}
}