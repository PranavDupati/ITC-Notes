#include <stdio.h>
int main() {
    float x1,y1,z1;
    float x2,y2,z2;
    float dotProduct;

    printf("Enter x1, y1 and z1:");
    scanf("%f %f %f", &x1, &y1, &z1); //use this to read the user input

    printf("Enter x2, y2 and z2:");
    scanf("%f %f %f", &x2, &y2, &z2); //use this to read the user input

    dotProduct = x1*x2 + y1*y2 + z1*z2;

    printf("The dot product is: %f\n", dotProduct);

    return 0;
}