#include <stdio.h>

int main() {
    int arr[5] = {1, 4, 5, 6, 9};
    int *f = arr;
    int *b = arr + 4;

    while(f < b) {
        printf("(%d, %d) ", *f, *b);
        f++;
        b--;
    }

    return 0;
}

