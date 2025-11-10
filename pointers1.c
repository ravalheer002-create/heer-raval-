#include <stdio.h>

int main() {
    int a = 10;
    int *p;
    p = &a;
    printf("Value of a using pointer: %d", *p);
    return 0;
}

