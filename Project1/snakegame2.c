#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <Windows.h>
#include <time.h>

int i, j, k = 0, height = 20, width = 20;
int gameover;
int score, pause;
int x, y, fruitx, fruity, flag, obstaclex, obstacley, itemx, itemy;
int bodyX[100], bodyY[100];
int length; // �� ���� ����
int highscore; // �ְ� ������ ������ ����
int num = 200;
int ig=0;
float second = 0;   // ���� �ð� ����
// Function to generate the fruit within the boundary
void setup()
{
    srand(time(NULL));
    
    gameover = 0;
    pause = 0;
    x = height / 2;
    y = width / 2;
    second = 0; // ���� �ð� 0 ����
    length = 0; // �ʱ� ���� 0 ����

    fruitx = 0;
    while (fruitx == 0) {
        fruitx = rand() % 20;
    }

    fruity = 0;
    while (fruity == 0) {
        fruity = rand() % 20;
    }

    // ��ֹ� ���� ����
    obstaclex = 0;
    while (obstaclex == 0) {
        obstaclex = rand() % 20;
    }

    obstacley = 0;
    while (obstacley == 0) {
        obstacley = rand() % 20;
    }

    // ������ ���� ����
    itemx = 0;
    while (itemx == 0)
    {
        itemx = rand() % 20;
    }

    itemy = 0;
    while (itemy == 0)
    {
        itemy = rand() % 20;
    }

    score = 0;

    // �ְ� ������ ���Ͽ��� �о����
    FILE* file;
    if (fopen_s(&file, "highscore.txt", "r") == 0) {
        fscanf_s(file, "%d", &highscore);  // ���Ͽ��� �ְ� ���� �б�
        fclose(file);
    }
    else {
        highscore = 0;  // ������ ������ �ְ� ������ 0���� ����
    }
}

// Function to draw the boundaries
void draw()
{
    // �ܼ� Ŀ���� ȭ���� ó������ �̵�
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // ȭ�� �׸���
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");  // �� �׸���
            }
            else {
                int SnakeBody = 0;
                for (int k = 0; k < length; k++) {
                    if (bodyX[k] == i && bodyY[k] == j) {
                        printf("o");  // �� ���� �׸���
                        SnakeBody = 1;
                        break;
                    }
                }

                if (!SnakeBody) {
                    if (i == x && j == y)
                        printf("0");  // �� �Ӹ� �׸���
                    else if (i == fruitx && j == fruity)
                        printf("*");  // ���� �׸���
                    else if (i == obstaclex && j == obstacley)
                        printf("X");  // ��ֹ� �׸���
                    else if (i == itemx && j == itemy && k >= 3)
                        printf("+");
                    else
                        printf(" ");  // �� ����
                }
            }
        }
        printf("\n");
    }

    // ���� ǥ��
    printf("score = %d", score);
    printf("\n");
    printf("high score = %d", highscore);  // �ְ� ���� ǥ��
    printf("\n");
    printf("press X to quit the game");
    printf("\n");
    printf("�����ð�: %0.f��", 20-second);
    if (pause==0)
        second += 0.2;  // �Ͻ������� �ƴ� �� �ð� ����. 
    fflush(stdout);  // ��� ���۸� ��� ����
    if (second >= 20)   // 20�ʰ� ������ ���� ����
    {
        gameover = 1;
    }
}

void input()
{
    if (_kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            ig = 0;
            break;
        case 's':
            flag = 2;
            ig = 0;
            break;
        case 'd':
            flag = 3;
            ig = 0;
            break;
        case 'w':
            flag = 4;
            ig = 0;
            break;
        case 'x':
            gameover = 1;
            break;
        // esc�� �Ͻ������� ����
        case 27:
            flag = 5;
            if (pause == 1)
                pause = 0;
            else
                pause = 1;
            ig = 1;
            break;
            // r�� �����
        case 'r':
            setup();
            break;
        }
    }
}

// Function for the logic behind each movement
void logic()
{
    {
        // ���� ��ġ ����
        int prevX = bodyX[0];
        int prevY = bodyY[0];
        int prev2X, prev2Y;
        bodyX[0] = x;
        bodyY[0] = y;

        // ���� ���� ��ġ ����
        for (int i = 1; i < length; i++) {
            prev2X = bodyX[i];
            prev2Y = bodyY[i];
            bodyX[i] = prevX;
            bodyY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (flag) {
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
        // ĳ������ ��ġ ����
        case 5:
            x = x;
            y = y;
            break;
        default:
            break;
        }
    }

    if (x == 0 || x == height + 1 || x == height - 1 || y == 0 || y == width + 1 || y == width - 1)
        gameover = 1;

    // �ڱ� ���� �浹�ߴ��� üũ
    for (int i = 0; i < length; i++) {
        if (bodyX[i] == x && bodyY[i] == y && ig == 0) {    // �Ͻ����� ���Ŀ� ��ȿ
            gameover = 1;
        }
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        length++; // ���� ���� ����
        k++; // k������ ������ ����
        second = 0; // ���� �ð� �ʱ�ȭ

        fruitx = 0;
        while (fruitx == 0) {
            fruitx = rand() % 20;
        }

        fruity = 0;
        while (fruity == 0) {
            fruity = rand() % 20;
        }
    }

    // ��ֹ��� �浹�ߴ��� üũ
    if (x == obstaclex && y == obstacley) {
        gameover = 1;
    }

    // ������ ����
    if (x == itemx && y == itemy)
    {
        itemx = 0;
        while (itemx == 0)
        {
            itemx = rand() % 20;
        }

        itemy = 0;
        while (itemy == 0)
        {
            itemy = rand() % 20;
        }

        score += 20; // �߰�����
        k = 0; //k �ʱ�ȭ
    }
}

void saveHighscore()
{
    if (score > highscore) {
        highscore = score;  // �ְ� ���� ����

        FILE* file;
        if (fopen_s(&file, "highscore.txt", "w") == 0) {
            fprintf(file, "%d", highscore); // �ְ� ���� ����
            fclose(file);
        }
    }
}

void speedControl()
{
    Sleep(num);

    static int lastScore = 0; // �ӵ��� ������ ������ ���� ����

    if (score != 0 && score / 50 > lastScore / 50) {  // ������ 50�� ����� ������ ��쿡��
        num -= 10; // �ӵ� ����
        lastScore = score;
    }
}


int main()
{
    setup();

    while (!gameover) {
        draw();  // ȭ�� �׸���
        input(); // �Է� ó��
        logic(); // ���� ���� ó��
        speedControl(); //�ӵ� ����
    }

    saveHighscore(); // ���� ���� �� �ְ� ���� ����
}