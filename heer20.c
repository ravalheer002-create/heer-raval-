#include <stdio.h>

int main() {
    float H, B, area;
    printf("Enter height and base: ");
    scanf("%f %f", &H, &B);

    area = (H * B) / 2;

    printf("Area of triangle = %.2f\n", area);
    return 0;
}

