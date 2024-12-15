#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <io.h> 
#include <Windows.h>
#include <time.h>

int i, j, k = 0, height = 20, width = 20;
int gameover, score, pause, game;

// 아이템 변수, itemx, itemy
int x, y, fruitx, fruity, flag, itemx, itemy;


void setup()
{

	gameover = 0;
	pause = 0;

	srand(time(NULL));

	x = height / 2;
	y = width / 2;

	fruitx = 0;
	while (fruitx == 0)
	{
		fruitx = rand() % 19;
	}

	fruity = 0;
	while (fruity == 0)
	{
		fruity = rand() % 19;
	}

	// 아이템 위치//
	itemx = 0;
	while (itemx == 0)
	{
		itemx = rand() % 19;
	}

	itemy = 0;
	while (itemy == 0)
	{
		itemy = rand() % 19;
	}

	score = 0;
	k = 0;
}


void draw()
{
	system("cls");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				printf("#");
			}
			else
			{
				if (i == x && j == y)
					printf("0");
				else if (i == fruitx && j == fruity)
				{
					printf("*");
				}
				// 아이템 생성. 
				else if (i == itemx && j == itemy && k >= 3)
				{
					printf("+");
				}
				else
					printf(" ");
			}
		}
		printf("\n");
	}

 
	printf("score = %d", score);
	printf("\n");
	printf("press X to quit the game");
}


void input()
{
	if (_kbhit())
	{
		switch (getch())
		{
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			gameover = 1;
			break;
			// esc로 정지
		case 27:
			flag = 6;
			if (pause == 1)
				pause = 0;
			else
				pause = 1;

			break;
			// r로 재시작
		case 'r':
			setup();
			break;
		}
	}
}


void logic()
{
	Sleep(200);
	if (pause == 0)
	{
		switch (flag)
		{
		case 1:
			y--;
			break;
		case 2:
			x++;
			break;
		case 3:
			y++;
			break;
		case 4:
			x--;
			break;
		case 5:
			gameover = 1;
			break;
		case 6:
			x = x;
			y = y;
			break;
		default:
			break;
		}
	}

	if (x == 0 || x == height + 1 || x == height - 1 || y == 0 || y == width + 1 || y == width - 1)
	{
		gameover = 1;
		printf("\ngameover!\n");
	}


	if (x == fruitx && y == fruity)
	{

		fruitx = 0;
		while (fruitx == 0)
		{
			fruitx = rand() % 19;
		}

		fruity = 0;
		while (fruity == 0)
		{
			fruity = rand() % 19;
		}

		score += 10;
		k++;
	}

	// 아아템 점수
	if (x == itemx && y == itemy)
	{
		itemx = 0;
		while (itemx == 0)
		{
			itemx = rand() % 19;
		}

		itemy = 0;
		while (itemy == 0)
		{
			itemy = rand() % 19;
		}

		score += 1000;
		k = 1;
	}
}


void main()
{
	int r, m, n, second=0;


			setup();
			while (!gameover)
			{
				// Function Call 
				draw();
				input();
				logic();
				// 일시정지시 출력. 
				if (pause == 1)
				{
					printf("일시정지 중. esc키를 눌러 재시작.");
				}
				printf("남은 시간: %d", second);
				second += 0.2;
				
			}

}
