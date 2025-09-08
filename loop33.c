#include <stdio.h>
#include <math.h>

int main() {
    int n, sq, temp, pow10 = 1, digits = 0;
    printf("Enter a number: ");
    scanf("%d", &n);

    sq = n * n;
    temp = n;

    // count digits in n
    while(temp > 0) {
        digits++;
        temp /= 10;
    }

    // make 10^digits
    for(int i = 1; i <= digits; i++) {
        pow10 *= 10;
    }

    if(sq % pow10 == n)
        printf("Automorphic number\n");
    else
        printf("Not an automorphic number\n");

    return 0;
}

