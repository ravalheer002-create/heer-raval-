#include <stdio.h>

int main() {
    int n, temp, rem, sum = 0;
    printf("Enter a number: ");
    scanf("%d", &n);

    temp = n;
    while(n > 0) {
        rem = n % 10;
        sum += rem * rem * rem;
        n /= 10;
    }

    if(temp == sum)
        printf("Armstrong number\n");
    else
        printf("Not an Armstrong number\n");

    return 0;
}

