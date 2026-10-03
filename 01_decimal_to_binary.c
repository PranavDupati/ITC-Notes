#include <stdio.h>

int main(void) {
    int n;
    int bits[32];
    int count = 0;

    printf("Enter a non-negative decimal integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    if (n == 0) {
        printf("Binary: 0\n");
        return 0;
    }

    while (n > 0) {
        bits[count] = n % 2;
        n = n / 2;
        count++;
    }

    printf("Binary: ");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
    printf("\n");
    return 0;
}
