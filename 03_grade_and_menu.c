#include <stdio.h>

int main(void) {
    int mark, choice;

    printf("Enter mark (0-100): ");
    if (scanf("%d", &mark) != 1 || mark < 0 || mark > 100) return 1;

    if (mark >= 90)
        printf("Grade A\n");
    else if (mark >= 75)
        printf("Grade B\n");
    else if (mark >= 50)
        printf("Grade C\n");
    else
        printf("Fail\n");

    printf("Enter 1 for area, 2 for perimeter: ");
    if (scanf("%d", &choice) != 1) return 1;

    switch (choice) {
        case 1:
            printf("Area = length * width\n");
            break;
        case 2:
            printf("Perimeter = 2 * (length + width)\n");
            break;
        default:
            printf("Invalid choice\n");
    }

    printf("%s\n", (mark >= 50) ? "Passed" : "Not passed");
    return 0;
}
