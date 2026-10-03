#include <stdio.h>
#include <math.h>
// to run this program, use: gcc programname.c -o programmane -lm
// then use ./programname
// this is because this uses imported libraries such as math.h
// sqrt() gives square root

int main() {
    int x1,y1;
    int x2,y2;
    int x3,y3;

    printf("Enter the coordinates for Point 1 (x y). Use spaces while entering the values: ");
    scanf("%d%d", &x1, &y1);

    printf("Enter the coordinates for Point 2 (x y). Use spaces while entering the values: ");
    scanf("%d%d", &x2, &y2);

    printf("Enter the coordinates for Point 3 (x y). Use spaces while entering the values: ");
    scanf("%d%d", &x3, &y3);

// this is basically the distance formula
    float side1 = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)); // the number 2 here is just the exponent
    float side2 = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2)); // the pow() function is just power 
    float side3 = sqrt(pow(x1-x3, 2) + pow(y1-y3, 2)); //  pow(x2-x1, 2) translates to (x2-x1) to the power of 2

// Validating the triangle below:
// The Triangle Inequality Theorem dictates that the sum of the lengths of any two sides of a triangle must be
// strictly greater than the third side.

    int sides_invalid=
        (side1+side2 <=side3) ||
        (side1+side3 <=side2) ||
        (side2+side3 <=side1);

    int valid_triangle=!sides_invalid;

    printf("\nValid triangle: %d\n", valid_triangle);

    return 0;

}