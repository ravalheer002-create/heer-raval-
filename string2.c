#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];
    int i;

    printf("Enter a string: ");
    gets(str);

    for(i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

    printf("String in lowercase: %s", str);
    return 0;
}

