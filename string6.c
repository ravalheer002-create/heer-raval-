#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];
    int result;

    printf("Enter first string: ");
    gets(str1);

    printf("Enter second string: ");
    gets(str2);

    result = strcmp(str1, str2);

    if(result == 0)
        printf("Both strings are equal");
    else if(result > 0)
        printf("First string is greater");
    else
        printf("Second string is greater");

    return 0;
}

