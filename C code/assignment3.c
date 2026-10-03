#include <stdio.h>
int main() {
    int n=14;
    int remaining=n;

    int fourth_digit=remaining%2;
    remaining=remaining/2;

    int third_digit=remaining%2;
    remaining=remaining/2;

    int second_digit=remaining%2;
    remaining=remaining/2;

    int first_digit=remaining%2;
    remaining=remaining/2;

    printf("The binary representation of %d is: %d%d%d%d\n", n, first_digit, second_digit, third_digit, fourth_digit);

    return 0;
}