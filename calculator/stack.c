#include <stdio.h>

#include "calc.h"

int sp = 0;
double val[MAXVAL];

void Push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    }
    else {
        printf("错误：栈已满，不能推入 %g\n", f);
    }
}

double Pop(void) {
    if (sp > 0) {
        return val[--sp];
    }
    else {
        printf("错误：栈为空\n");
        return 0.0;
    }
}
