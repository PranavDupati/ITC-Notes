#include <stdio.h>
int main() {
    float a=1, b=1;
    printf("Enter a value for length and width:");
    scanf("%f%f", &a, &b);
    float area = a*b;
    printf("The area of the rectangle is: %f\n", area);
    float perimeter = 2*(a+b);
    printf("The perimeter of the rectangle is: %f\n", perimeter);
    return 0;
}