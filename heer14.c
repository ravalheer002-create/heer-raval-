#include <stdio.h>

int main() {
    float c, f;
    printf("Enter Celsius: ");
    scanf("%f", &c);

    f = (9.0 / 5.0 * c) + 32;

    printf("%.2f °C = %.2f °F\n", c, f);
    return 0;
}

