#include <stdio.h>

int main(void) {
    int n, a[100];
    int sum = 0, even_count = 0;

    printf("How many values (1-100)? ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) return 1;

    for (int i = 0; i < n; i++) {
        printf("a[%d]: ", i);
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    int maximum = a[0];
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (a[i] > maximum) maximum = a[i];
        if (a[i] % 2 == 0) even_count++;
    }

    printf("Sum = %d\n", sum);
    printf("Maximum = %d\n", maximum);
    printf("Even values = %d\n", even_count);
    printf("Average = %.2f\n", (float)sum / n);
    return 0;
}
