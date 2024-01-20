#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = GetOp(s)) != EOF) {
        switch (type) {
        case NUMBER:
            Push(atof(s));
            break;
        case '+':
            Push(Pop() + Pop());
            break;
        case '*':
            Push(Pop() * Pop());
            break;
        case '-':
            op2 = Pop();
            Push(Pop() - op2);
            break;
        case '/':
            op2 = Pop();
            if (op2 != 0.0) {
                Push(Pop() / op2);
            }
            else {
                printf("错误：0作为除数\n");
            }
            break;
        case '\n':
            printf("\t%.8g\n", Pop());
            break;
        default:
            printf("错误：未知指令 %s", s);
            break;
        }
    }
    return 0;
}
