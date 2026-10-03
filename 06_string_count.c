#include <stdio.h>
#include <string.h>

int main(void) {
    char word[50];
    int vowels = 0;

    printf("Enter one word: ");
    if (scanf("%49s", word) != 1) return 1;

    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            vowels++;
        }
    }

    printf("Length = %d\n", (int)strlen(word));
    printf("Vowels = %d\n", vowels);
    return 0;
}
