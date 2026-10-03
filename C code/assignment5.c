#include <stdio.h>
#include <math.h>
// to run this program, use: gcc programname.c -o programmane -lm
// then use ./programname
// this is because this uses imported libraries such as math.h
// sqrt() gets the square root of the number

int main() {
    float x1,y1,x2,y2;

    printf("The first point for x1 and y1 (use spaces in between numbers): ");
    scanf("%f%f", &x1, &y1);

    printf("The second point for x2 and y2 (use spaces in between numbers): ");
    scanf("%f%f", &x2, &y2);

    float distance= sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));

    printf("The Euclidean distance is: %f\n", distance);

    return 0;

}