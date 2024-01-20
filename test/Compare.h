#include <stdlib.h>

#ifndef COMPARE_H
#define COMPARE_H

int NumCmp(char *s1, char *s2);
int StrCmp(char *s, char *t);

int NumCmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    }
    else if (v1 > v2) {
        return 1;
    }
    else {
        return 0;
    }
}

int StrCmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++;
        t++;
    }
    return *s - *t;
}

#endif