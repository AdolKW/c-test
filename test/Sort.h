#ifndef SORT_H
#define SORT_H

void QuickSort(void *v[], int left, int right, int (*comp)(void *, void *));
void Swap(void *v[], int i, int j);

void QuickSort(void *v[], int left, int right, int (*Comp)(void *, void *)) {
    int i, last;
    if (left >= right) {
        return;
    }
    Swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (((*Comp)(v[i], v[left]) < 0)) {
            Swap(v, ++last, i);
        }
    }
    Swap(v, left, last);
    QuickSort(v, left, last - 1, Comp);
    QuickSort(v, last + 1, right, Comp);
}

void Swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#endif