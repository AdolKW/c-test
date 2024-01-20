#ifndef ALLOC_H
#define ALLOC_H

#define ALLOCSIZE 100000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *Alloc(int n);
void Afree(char *p);

char *Alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else {
        return 0;
    }
}

void Afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}

#endif