#include <stdio.h>

int main() {
    float R, area;
    printf("Enter radius: ");
    scanf("%f", &R);

    area = (22.0 / 7.0) * R * R;

    printf("Area of circle = %.2f\n", area);
    return 0;
}

