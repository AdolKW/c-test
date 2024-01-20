#include <stdio.h>

#ifndef GETCH_H
#define GETCH_H

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int Getch(void);
void UnGetch(int c);

int Getch(void) {
    if (bufp > 0) {
        bufp--;
        return buf[bufp];
    }
    else {
        return getchar();
    }
}

void UnGetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("回退：太多字符了");
    }
    else {
        buf[bufp++] = c;
    }
}

#endif