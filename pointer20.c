#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;
    int **q = &p;
    int ***r = &q;

    printf("Address of a: %p\n", &a);
    printf("Address of p: %p\n", &p);
    printf("Address of q: %p\n", &q);
    printf("Address of r: %p\n", &r);
    printf("Value chain: %d", ***r);
    return 0;
}

