#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <Windows.h>
#include <time.h>

int i, j, item = 0, height = 20, width = 20;
int gameover, gameout=0;
int score, pause;
int x, y, fruitx, fruity, flag, obstaclex, obstacley, itemx, itemy;
int bodyX[100], bodyY[100];
int length; // 뱀 길이 변수
int highscore; // 최고 점수를 저장할 변수
int num;
int ig=0;
float second = 0;   // 남은 시간 변수
// Function to generate the fruit within the boundary
void setup()
{
    srand(time(NULL));
    num = 200; // 속도 초기화
    score = 0; // 점수 초기화
    gameover = 0;
    gameout = 0; // gameout 초기화
    pause = 0; // 일시정지 해제
    x = height / 2;
    y = width / 2;
    second = 0; // 남은 시간 0 설정
    length = 0; // 초기 길이 0 설정
    item = 0; // 아이템 변수 초기화

    fruitx = 0;
    while (fruitx == 0) {
        fruitx = rand() % 18;
    }

    fruity = 0;
    while (fruity == 0) {
        fruity = rand() % 18;
    }

    // 장애물 랜덤 생성
    obstaclex = 0;
    while (obstaclex == 0) {
        obstaclex = rand() % 18;
    }

    obstacley = 0;
    while (obstacley == 0) {
        obstacley = rand() % 18;
    }

    // 아이템 랜덤 생성
    itemx = 0;
    while (itemx == 0)
    {
        itemx = rand() % 18;
    }

    itemy = 0;
    while (itemy == 0)
    {
        itemy = rand() % 18;
    }


    // 최고 점수를 파일에서 읽어오기
    FILE* file;
    if (fopen_s(&file, "highscore.txt", "r") == 0) {
        fscanf_s(file, "%d", &highscore);  // 파일에서 최고 점수 읽기
        fclose(file);
    }
    else {
        highscore = 0;  // 파일이 없으면 최고 점수를 0으로 설정
    }
}

// Function to draw the boundaries
void draw()
{
    // 콘솔 커서를 화면의 처음으로 이동
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // 화면 그리기
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");  // 벽 그리기
            }
            else {
                int SnakeBody = 0;
                for (int k = 0; k < length; k++) {
                    if (bodyX[k] == i && bodyY[k] == j) {
                        printf("o");  // 뱀 몸통 그리기
                        SnakeBody = 1;
                        break;
                    }
                }

                if (!SnakeBody) {
                    if (i == x && j == y)
                        printf("0");  // 뱀 머리 그리기
                    else if (i == fruitx && j == fruity)
                        printf("*");  // 과일 그리기
                    else if (i == obstaclex && j == obstacley)
                        printf("X");  // 장애물 그리기
                    else if (i == itemx && j == itemy && item >= 3)
                        printf("+");
                    else
                        printf(" ");  // 빈 공간
                }
            }
        }
        printf("\n");
    }

    // 점수 표시
    printf("score = %d", score);
    printf("\n");
    printf("high score = %d", highscore);  // 최고 점수 표시
    printf("\n");
    printf("press X to quit the game");
    printf("\n");
    printf("남은시간: %0.f초", 20-second);
    if (pause==0)
        second += 0.2;  // 일시정지가 아닐 때 시간 증가. 
    fflush(stdout);  // 출력 버퍼를 즉시 갱신
    if (second >= 20)   // 20초가 넘으면 게임 종료
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
            gameout = 1;
            break;
        // esc로 일시정지와 해제
        case 27:
            flag = 5;
            pause = !pause;
            ig = 1;
            break;
            // r로 재시작
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
        // 뱀의 위치 저장
        int prevX = bodyX[0];
        int prevY = bodyY[0];
        int prev2X, prev2Y;
        bodyX[0] = x;
        bodyY[0] = y;

        // 뱀의 몸통 위치 조정
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
        // 캐릭터의 위치 고정
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

    // 자기 몸에 충돌했는지 체크
    for (int i = 0; i < length; i++) {
        if (bodyX[i] == x && bodyY[i] == y && ig == 0) {    // 일시정지 직후엔 무효
            gameover = 1;
        }
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        length++; // 뱀의 길이 증가
        item++; // item 증가로 아이템 생성
        second = 0; // 남은 시간 초기화

        fruitx = 0;
        while (fruitx == 0) {
            fruitx = rand() % 18;
        }

        fruity = 0;
        while (fruity == 0) {
            fruity = rand() % 18;
        }
    }

    // 장애물에 충돌했는지 체크
    if (x == obstaclex && y == obstacley) {
        gameover = 1;
    }

    // 아이템 점수
    if (x == itemx && y == itemy)
    {
        itemx = 0;
        while (itemx == 0)
        {
            itemx = rand() % 18;
        }

        itemy = 0;
        while (itemy == 0)
        {
            itemy = rand() % 18;
        }

        score += 20; // 추가점수
        item = 0; //k 초기화
    }
}

void saveHighscore()
{
    if (score > highscore) {
        highscore = score;  // 최고 점수 갱신

        FILE* file;
        if (fopen_s(&file, "highscore.txt", "w") == 0) {
            fprintf(file, "%d", highscore); // 최고 점수 저장
            fclose(file);
        }
    }
}

void speedControl()
{
    Sleep(num);

    static int lastScore = 0; // 속도가 조정된 마지막 점수 추적

    if (score != 0 && score / 50 > lastScore / 50) {  // 점수가 50의 배수에 도달한 경우에만
        num -= 10; // 속도 증가
        lastScore = score;
    }
}


int main()
{
    setup();

    while (!gameout) {
        if (gameover==1) { // 게임 오버 상태일 때
            printf("\nr키를 눌러서 재시작\n");
            while (gameover) { // 게임 오버 상태에서 멈추고, 사용자가 'r'을 누를 때까지 기다림
                input(); // 'r' 입력을 처리하여 게임을 재시작
            }
        }
        else {
            if (pause==0) { // pause 상태가 아닐 때
                draw();
                input();
                logic();        
                speedControl(); // 속도 조절
            }
            else { // pause 상태일 때
                input();
            }
        }
    }
    saveHighscore(); // 게임 종료 시 최고 점수 저장
}
