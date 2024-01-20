#include <conio.h>
#include <stdio.h>
#include <windows.h>

struct {
    int x[4], y[4];
    char name;
} mino;

int gameMap[21][24];

HANDLE handle;
CONSOLE_CURSOR_INFO cursorInfo;
COORD coord;

void DrawBorder();
void DrawBlock(int x, int y, WORD color);
void Init();
void Start();
void DrawMino();
void UpdateMino();
void ClearMino(int x, int y);
void MoveMino();
int LeftDistance();
int RightDistance();
int BottomDistance();
void CheckBottom();

int main() {
    Start();
    getchar();
    return 0;
}

void CheckBottom() {
    int bottomDistance = BottomDistance();
    if (bottomDistance == 20) {
        for (int i = 0; i < 4; i++) {
            gameMap[mino.y[i]][mino.x[i]] = 1;
        }
        for (int i = 0; i < 4; i++) {
            mino.x[i] = 2;
            mino.y[i] = i;
        }
    }
}

int BottomDistance() {
    int maxIdx = 0;
    for (int i = 0; i < 4; i++) {
        if (mino.y[i] > mino.y[maxIdx]) {
            maxIdx = i;
        }
    }
    return mino.y[maxIdx];
}

int RightDistance() {
    int maxIdx = 0;
    for (int i = 0; i < 4; i++) {
        if (mino.x[i] > mino.x[maxIdx]) {
            maxIdx = i;
        }
    }
    return mino.x[maxIdx];
}

int LeftDistance() {
    int minIdx = 0;
    for (int i = 1; i < 4; i++) {
        if (mino.x[i] < mino.x[minIdx]) {
            minIdx = i;
        }
    }
    return mino.x[minIdx];
}

void MoveMino() {
    int bottomDistance = BottomDistance();
    if (bottomDistance == 19) {
        for (int i = 0; i < 4; i++) {
            gameMap[mino.y[i]][mino.x[i]] = 1;
        }
        for (int i = 0; i < 4; i++) {
            mino.x[i] = 2;
            mino.y[i] = i;
        }
        return;
    }
    UpdateMino();
    for (int i = 0; i < 4; i++) {
        mino.y[i]++;
    }
    if (kbhit()) {
        char key = getch();
        int leftDistance = LeftDistance();
        int rightDistance = RightDistance();
        switch (key) {
        case 'W':
        case 'w':
            break;
        case 'S':
        case 's':
            for (int i = 0; i < 4; i++) {
                mino.y[i]++;
            }
            break;
        case 'A':
        case 'a':
            if (leftDistance > 2) {
                for (int i = 0; i < 4; i++) {
                    mino.x[i] -= 2;
                }
            }
            break;
        case 'D':
        case 'd':

            if (rightDistance < 20) {
                for (int i = 0; i < 4; i++) {
                    mino.x[i] += 2;
                }
            }
            break;
        default:
            break;
        }
    }
}

void ClearMino(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
    printf("  ");
}

void UpdateMino() {
    for (int i = 0; i < 4; i++) {
        ClearMino(mino.x[i], mino.y[i]);
    }
}

void DrawMino() {
    if (mino.name == 'I') {
        for (int i = 0; i < 4; i++) {
            DrawBlock(mino.x[i], mino.y[i], FOREGROUND_BLUE | FOREGROUND_GREEN);
        }
    }
}

void Start() {
    Init();
    DrawBorder();
    while (1) {
        MoveMino();
        DrawMino();
        Sleep(500);
    }
}

void Init() {
    for (int i = 0; i < 4; i++) {
        mino.x[i] = 2;
        mino.y[i] = i;
    }
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 24; j++) {
            gameMap[i][j] = 0;
        }
    }

    mino.name = 'I';
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &cursorInfo);
}

void DrawBlock(int x, int y, WORD color) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color);
    printf("¡õ");
}

void DrawBorder() {
    for (int i = 0; i <= 20; i++) {
        DrawBlock(0, i, FOREGROUND_BLUE);
        DrawBlock(22, i, FOREGROUND_BLUE);
    }
    for (int i = 2; i <= 20; i += 2) {
        DrawBlock(i, 20, FOREGROUND_BLUE);
    }
}