#ifndef CALC_H
#define CALC_H

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

void Push(double);
double Pop(void);
int GetOp(char[]);
int Getch(void);
void UnGetch(int);

#endif
