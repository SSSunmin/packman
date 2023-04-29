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
int i =0;
int j =0;

void Freemap()
{
	
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
    
	Drawmap2();
	Drawmap();

	while (isedit)
	{
		Inputkey();
	}
}