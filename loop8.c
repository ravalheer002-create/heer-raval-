#include <stdio.h>

int main() {
    int n, i, count = 0, sum = 0;
    printf("Enter value of n: ");
    scanf("%d", &n);

    for(i = 1; count < n; i += 2) {
        sum += i;
        count++;
    }

    printf("Sum of first %d odd numbers = %d\n", n, sum);
    return 0;
}

