#include <stdio.h>

int main() {
    float L, B, area, perimeter;
    printf("Enter length and breadth: ");
    scanf("%f %f", &L, &B);

    area = L * B;
    perimeter = 2 * (L + B);

    printf("Area = %.2f, Perimeter = %.2f\n", area, perimeter);
    return 0;
}
