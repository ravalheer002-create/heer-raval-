#include <stdio.h>

int main() {
    float dollars, rupees, pounds;
    printf("Enter dollars: ");
    scanf("%f", &dollars);

    rupees = dollars * 48;
    pounds = rupees / 70;

    printf("%.2f dollars = %.2f pounds\n", dollars, pounds);
    return 0;
}

