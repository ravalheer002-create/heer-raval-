
#include <stdio.h>

int main() {
    float L, area, perimeter;
    printf("Enter side of square: ");
    scanf("%f", &L);

    area = L * L;
    perimeter = 4 * L;

    printf("Area = %.2f, Perimeter = %.2f\n", area, perimeter);
    return 0;
}
