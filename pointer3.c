#include <stdio.h>

int main() {
    int a = 25;
    int *p = &a;
    printf("Address stored in pointer: %p\n", p);
    printf("Value at that address: %d", *p);
    return 0;
}

