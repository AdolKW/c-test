#include <stdio.h>

#include "Compare.h"
#include "GetLine.h"
#include "Getch.h"
#include "Sort.h"
#include "Str.h"
#include "ctype.h"

void PrintDecimal(int n);
void PrintBinary(int num, int argc, char *argv[]);
int BinarySearch(int target, int arr[], int size);
void BaseConv(int num, char str[], int base);
int GetInt(int *pn);

struct Point {
    int x;
    int y;
};

struct Rect {
    struct Point leftUp;
    struct Point rightDown;
    int arr1[2];
    int arr2[2];
    char *attribute;
};

struct Test {
    int n;
    char *str;
};

void Test(char **str) {
    (*str)++;
    return;
}

int main() {
    int nLines = 0;
    char numeric = 0;
    void *p = linePtr;
    if ((nLines = ReadLines(linePtr, MAX_LINES)) >= 0) {
        QuickSort((void **)linePtr, 0, nLines - 1,
                  (int (*)(void *, void *))(numeric ? NumCmp : StrCmp));
        QuickSort((void *)linePtr, 0, nLines - 1,
                  (int (*)(void *, void *))(numeric ? NumCmp : StrCmp));
        WriteLines(linePtr, nLines);
    }
    return 0;
}

int GetInt(int *pn) {
    int c, sign;
    while (isspace(c = Getch())) {
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        UnGetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = Getch();
    }
    for (*pn = 0; isdigit(c); c = Getch()) {
        *pn = 10 * (*pn) + (c - '0');
    }
    *pn *= sign;
    if (c != EOF) {
        UnGetch(c);
    }
    return c;
}

void PrintDecimal(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10) {
        PrintDecimal(n / 10);
    }
    putchar(n % 10 + '0');
}

void PrintBinary(int num, int argc, char *argv[]) {
    printf("%s\n", *argv);
    int maxIdx = sizeof(num) * 8 - 1;
    while (maxIdx >= 0 && ((num >> maxIdx) & 1) == 0) {
        maxIdx--;
    }
    int padding = 8 - ((maxIdx + 1) % 8);
    if (padding != 0 && padding != 8) {
        for (int i = 0; i < padding; i++) {
            putchar('0');
        }
    }
    for (int i = maxIdx; i >= 0; i--) {
        int bit = (num >> i) & 1;
        putchar(bit + '0');
        if (i % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int BinarySearch(int target, int arr[], int size) {
    int left = 0, right = size - 1;
    int mid = (right + left) >> 1;
    while (left <= right && target != arr[mid]) {
        if (target > arr[mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
        mid = (right + left) >> 1;
    }
    return target == arr[mid] ? mid : -1;
}

void BaseConv(int num, char str[], int base) {
    int i = 0, sign;
    if ((sign = num) < 0) {
        num = -num;
    }
    do {
        int digit = num % base;
        if (digit < 10) {
            str[i++] = digit + '0';
        }
        else {
            str[i++] = digit - 10 + 'A';
        }
        num /= base;
    } while (num > 0);

    if (sign < 0) {
        str[i++] = '-';
    }

    str[i] = '\0';

    StrRev(str);
}