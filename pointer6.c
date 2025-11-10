#include <stdio.h>

int main() {
    char str[] = "HELLO";
    char *p = str;

    while(*p != '\0') {
        printf("%c\n", *p);
        p++;
    }
    return 0;
}

