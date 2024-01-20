#include "Alloc.h"

#ifndef STR_H
#define STR_H

void StrCopy(char *s, char *t);
char *StrCat(char strFront[], char strRear[]);
int StrLen(char *str);
void StrRev(char str[]);
int StrIdx(char mainStr[], char subStr[]);

void StrCopy(char *s, char *t) {
    while (*t != '\0') {
        *s = *t;
        s++;
        t++;
    }
    *s = '\0';
}

char *StrCat(char strFront[], char strRear[]) {
    int l1 = StrLen(strFront), l2 = StrLen(strRear);
    char *newStr = Alloc(l1 + l2 + 1);
    int i = 0, j = 0;
    while (strFront[i] != '\0') {
        newStr[i] = strFront[i];
        i++;
    }
    while (strRear[j] != '\0') {
        newStr[i] = strRear[j];
        i++;
        j++;
    }
    newStr[i] = '\0';
    return newStr;
}

int StrLen(char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

void StrRev(char str[]) {
    int i, j;
    char temp;
    for (i = 0, j = StrLen(str) - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int StrIdx(char mainStr[], char subStr[]) {
    for (int i = 0; mainStr[i] != '\0'; i++) {
        int j = 0;
        while (mainStr[i + j] != '\0' && mainStr[i + j] == subStr[j]) {
            j++;
        }
        if (j > 0 && subStr[j] == '\0') {
            return i;
        }
    }
    return -1;
}

#endif