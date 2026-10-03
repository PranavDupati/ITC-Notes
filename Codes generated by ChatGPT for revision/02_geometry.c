#include <math.h>
#include <stdio.h>

int main(void) {
    float x1, y1, x2, y2;

    printf("Enter point 1 (x y): ");
    if (scanf("%f %f", &x1, &y1) != 2) return 1;
    printf("Enter point 2 (x y): ");
    if (scanf("%f %f", &x2, &y2) != 2) return 1;

    float dx = x1 - x2;
    float dy = y1 - y2;
    float manhattan = fabsf(dx) + fabsf(dy);
    float euclidean = sqrtf(dx * dx + dy * dy);

    printf("Manhattan distance: %.2f\n", manhattan);
    printf("Euclidean distance: %.2f\n", euclidean);
    return 0;
}
