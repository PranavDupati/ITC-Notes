#include <stdio.h>

int main(void) {
    int a[2][2], b[2][2], sum[2][2];

    printf("Enter 4 values for matrix A:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (scanf("%d", &a[i][j]) != 1) return 1;
        }
    }

    printf("Enter 4 values for matrix B:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (scanf("%d", &b[i][j]) != 1) return 1;
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("A + B:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
    return 0;
}
