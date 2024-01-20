#include <stdio.h>

int nums[100];

int main() {
    int n, count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", nums + i);
        count += nums[i];
    }
    int maxCount = 0, tempCount = count;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            tempCount = count;
            for (int k = 0; k < n; k++) {
                if (k >= i && k <= j) {
                    if (nums[k] == 0) {
                        tempCount++;
                    }
                    else {
                        tempCount--;
                    }
                }
            }
            if (tempCount > maxCount) {
                maxCount = tempCount;
            }
        }
    }
    printf("%d", maxCount);
    while (getchar() != EOF) {
    }
    return 0;
}
