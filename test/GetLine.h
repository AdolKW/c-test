#include <stdio.h>

#include "Alloc.h"
#include "Str.h"

#ifndef GETLINE_H
#define GETLINE_H

#define MAX_LEN 1000
#define MAX_LINES 5000

char *linePtr[MAX_LINES];

int GetLine(char *line, int max);
int ReadLines(char *linePtr[], int maxLines);
void WriteLines(char *linePtr[], int nLines);

int GetLine(char *line, int max) {
    int c, i;
    // max--;
    // while (max > 0 && (c = getchar()) != EOF && c != '\n') {
    //     line[i] = c;
    //     i++;
    //     max--;
    // }
    for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

int ReadLines(char *linePtr[], int maxLines) {
    int len, nLines = 0;
    char *p, line[MAX_LEN];
    while ((len = GetLine(line, MAX_LEN)) > 0) {
        if (nLines >= maxLines || (p = Alloc(len + 1)) == NULL) {
            return -1;
        }
        else {
            line[len - 1] = (line[len - 1] == '\n') ? '\0' : line[len - 1];
            StrCopy(p, line);
            linePtr[nLines] = p;
            nLines++;
        }
    }
    return nLines;
}

void WriteLines(char *linePtr[], int nLines) {
    int lines = nLines;
    while (nLines > 0) {
        nLines--;
        printf("%d行：%s\n", lines - nLines, *linePtr++);
    }
}

#endif