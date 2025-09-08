
#include <stdio.h>

int main() {
    int i, n;
    printf("Enter value of n: ");
    scanf("%d", &n);

    printf("First %d natural numbers:\n", n);
    for(i = 1; i <= n; i++) {
        printf("%d ", i);
    }
    return 0;
}
