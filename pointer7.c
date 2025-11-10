#include <stdio.h>

int main() {
    int a = 50;
    int *p = &a;
    int **pp = &p;

    printf("Value using double pointer: %d", **pp);
    return 0;
}

