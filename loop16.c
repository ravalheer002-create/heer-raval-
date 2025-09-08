#include <stdio.h>
#include <math.h>

int main() {
    int x, y, result;
    printf("Enter base (x): ");
    scanf("%d", &x);
    printf("Enter exponent (y): ");
    scanf("%d", &y);

    result = pow(x, y);

    printf("%d^%d = %d\n", x, y, result);
    return 0;
}
