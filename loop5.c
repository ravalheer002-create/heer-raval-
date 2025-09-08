#include <stdio.h>

int main() {
    int i, n, count = 0;
    printf("Enter value of n: ");
    scanf("%d", &n);

    printf("First %d odd numbers:\n", n);
    for(i = 1; count < n; i += 2) {
        printf("%d ", i);
        count++;
    }
    return 0;
}

