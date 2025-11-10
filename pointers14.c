#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = &arr[1], *q = &arr[3];
    *p = *p + *q;
    *q = *p - *q;
    *p = *p - *q;

    for(int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    return 0;
}

