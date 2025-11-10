#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i;

    printf("Enter a string: ");
    gets(str);

    for(i = strlen(str) - 1; i >= 0; i--)
        printf("%c\n", str[i]);

    return 0;
}

