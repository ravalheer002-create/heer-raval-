#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;
    printf("Third element using pointer: %d", *(p + 2));
    return 0;
}

