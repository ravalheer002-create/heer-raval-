#include <stdio.h>

int main() {
    float a, b, result;
    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);

    result = a / b;

    printf("Quotient = %.2f\n", result);
    return 0;
}
