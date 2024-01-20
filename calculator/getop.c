#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

int GetOp(char s[]) {
    int i, c;

    while ((s[0] = c = Getch()) == ' ' || c == '\t') {
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 1;
    if (isdigit(c)) {
        while (isdigit(s[i] = c = Getch())) {
            i++;
        }
    }
    if (c == '.') {
        while (isdigit(s[i] = c = Getch())) {
            i++;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        UnGetch(c);
    }
    return NUMBER;
}
