#include <stdio.h>

int main() {
    float gross, discount, net;

    printf("Enter Gross Sales: ");
    scanf("%f", &gross);

    if(gross > 20000)
        discount = gross * 0.15;
    else if(gross > 10000)
        discount = gross * 0.10;
    else
        discount = gross * 0.05;

    net = gross - discount;

    printf("Net Sales = %.2f\n", net);

    return 0;
}

