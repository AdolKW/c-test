#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 48
#define HEIGHT 48
#define SNAKE_SIZE 100000
#define DEFAULT_SLEEP_TIME 250
#define DEFAULT_IS_AUTO 0
#define DEFAULT_DIR RIGHT
#define DEFAULT_HEAD_X WIDTH / 2
#define DEFAULT_HEAD_Y HEIGHT / 2
#define DEFAULT_IS_COLLISION 0

struct {
    int x, y;
    char isExist;
} food;
struct {
    int size, life;
    int x[SNAKE_SIZE], y[SNAKE_SIZE];
} snake;

enum { UP, DOWN, LEFT, RIGHT } dir;
enum { WALL, ROAD, HEAD, BODY, FOOD };

const char DIRECTION[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

char gameMap[HEIGHT][WIDTH];
char lastMap[HEIGHT][WIDTH];
int sleepTime;
char isAuto;
char isCollision;

void DrawGameMap();
void Init();
void UpdateSnake();
void DetectKeyDown();
void CreateFood();
void EatFood();
void AutoMove();
void DrawInterface();
void PrintInfo(int x, int y, const char* info, ...);
void CollisionHanding();
void Start();

int main() {
    Start();
    return 0;
}

void Start() {
    system("cls");
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    Init();
    while (1) {
        if (snake.life <= 0) {
            PrintInfo(0, HEIGHT, "游戏结束！按下空格重新游戏，按下ESC退出");
            char key = _getch();
            if (key == ' ') {
                Start();
            }
            else if (key == 27) {
                break;
            }
            else {
                continue;
            }
        }
        DetectKeyDown();
        if (isAuto) {
            AutoMove();
        }
        CreateFood();
        EatFood();
        UpdateSnake();
        DrawInterface();
        Sleep(sleepTime);
    }
}

void CollisionHanding() {
    if ((gameMap[snake.y[0]][snake.x[0]] == WALL ||
         gameMap[snake.y[0]][snake.x[0]] == BODY) &&
        isCollision) {
        snake.life--;
    }
    else {
        snake.x[0] = (snake.x[0] + WIDTH) % WIDTH;
        snake.y[0] = (snake.y[0] + HEIGHT) % HEIGHT;
    }
}

void PrintInfo(int x, int y, const char* info, ...) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
    va_list args;
    va_start(args, info);
    vprintf(info, args);
    va_end(args);
}

void DrawInterface() {
    for (int i = 0; i < HEIGHT; i++) {
        PrintInfo(WIDTH * 2 + 5, i, "|");
    }

    PrintInfo(WIDTH * 2 + 10, 2, "蛇身长度：%4d", snake.size);
    PrintInfo(WIDTH * 2 + 10, 4, "吃到食物的个数：%4d", snake.size - 1);
    PrintInfo(WIDTH * 2 + 10, 6, "当前速度：%4d", sleepTime);
    PrintInfo(WIDTH * 2 + 10, 8, "剩余生命：%4d", snake.life);
    PrintInfo(WIDTH * 2 + 10, 10, "是否自动寻路：%s", isAuto ? "是" : "否");
    PrintInfo(WIDTH * 2 + 10, 12, "碰撞是否开启：%s",
              isCollision ? "是" : "否");
    PrintInfo(WIDTH * 2 + 10, 14, "WASD控制移动");
    PrintInfo(WIDTH * 2 + 10, 16, "K开关自动寻路,");
    PrintInfo(WIDTH * 2 + 10, 18, "J、L调节速度");
    PrintInfo(WIDTH * 2 + 10, 20, "H开关碰撞");
    DrawGameMap();
}

void AutoMove() {
    if (food.x > snake.x[0]) {
        dir = RIGHT;
    }
    else if (food.x < snake.x[0]) {
        dir = LEFT;
    }
    else if (food.y > snake.y[0]) {
        dir = DOWN;
    }
    else if (food.y < snake.y[0]) {
        dir = UP;
    }
}

void EatFood() {
    if (snake.x[0] == food.x && snake.y[0] == food.y) {
        snake.size++;
        food.isExist = 0;
        gameMap[food.y][food.x] = ROAD;
    }
}

void CreateFood() {
    if (!food.isExist) {
        do {
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
        } while (gameMap[food.y][food.x] != ROAD);
        gameMap[food.y][food.x] = FOOD;
        food.isExist = 1;
    }
}

void DetectKeyDown() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'w':
        case 'W':
            dir = (dir != DOWN) ? UP : DOWN;
            break;
        case 's':
        case 'S':
            dir = (dir != UP) ? DOWN : UP;
            break;
        case 'a':
        case 'A':
            dir = (dir != RIGHT) ? LEFT : RIGHT;
            break;
        case 'd':
        case 'D':
            dir = (dir != LEFT) ? RIGHT : LEFT;
            break;
        case 'k':
        case 'K':
            isAuto = !isAuto;
            break;
        case 'j':
        case 'J':
            sleepTime += 100;
            break;
        case 'l':
        case 'L':
            if (sleepTime > 0) {
                sleepTime =
                    (sleepTime <= 100) ? sleepTime - 10 : sleepTime - 100;
            }
            break;
        case 'h':
        case 'H':
            isCollision = !isCollision;
            break;
        }
    }
}

void UpdateSnake() {
    if ((snake.x[0] != food.x || snake.y[0] != food.y) &&
        gameMap[snake.y[snake.size - 1]][snake.x[snake.size - 1]] != WALL) {
        gameMap[snake.y[snake.size - 1]][snake.x[snake.size - 1]] = ROAD;
    }
    for (int i = snake.size - 1; i >= 1; i--) {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
        if (lastMap[snake.y[i]][snake.x[i]] != WALL) {
            gameMap[snake.y[i]][snake.x[i]] = BODY;
        }
    }
    snake.x[0] += DIRECTION[dir][0];
    snake.y[0] += DIRECTION[dir][1];
    CollisionHanding();
    if (lastMap[snake.y[0]][snake.x[0]] != WALL) {
        gameMap[snake.y[0]][snake.x[0]] = HEAD;
    }
}

void Init() {
    srand((unsigned int)time(NULL));
    food.isExist = 0;
    snake.size = 1;
    snake.life = 1;
    snake.x[0] = DEFAULT_HEAD_X;
    snake.y[0] = DEFAULT_HEAD_Y;
    dir = DEFAULT_DIR;
    sleepTime = DEFAULT_SLEEP_TIME;
    isAuto = DEFAULT_IS_AUTO;
    isCollision = DEFAULT_IS_COLLISION;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                gameMap[i][j] = WALL;
            }
            else {
                gameMap[i][j] = ROAD;
            }
            lastMap[i][j] = -1;
        }
    }
}

void DrawGameMap() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &cursorInfo);
    COORD coord;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (gameMap[i][j] != lastMap[i][j]) {
                coord.X = j * 2;
                coord.Y = i;
                SetConsoleCursorPosition(handle, coord);
                if (gameMap[i][j] == WALL) {
                    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
                    printf("□");
                }
                else if (gameMap[i][j] == ROAD) {
                    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                    printf("  ");
                }
                else if (gameMap[i][j] == HEAD) {
                    SetConsoleTextAttribute(handle,
                                            FOREGROUND_RED | FOREGROUND_BLUE);
                    printf("◇");
                }
                else if (gameMap[i][j] == BODY) {
                    SetConsoleTextAttribute(handle, FOREGROUND_RED);
                    printf("○");
                }
                else if (gameMap[i][j] == FOOD) {
                    SetConsoleTextAttribute(handle,
                                            FOREGROUND_RED | FOREGROUND_GREEN);
                    printf("☆");
                }
                lastMap[i][j] = gameMap[i][j];
            }
        }
    }
}