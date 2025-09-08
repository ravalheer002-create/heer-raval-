#include <stdio.h>

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    if(a > b)
        printf("Largest = %d, Smallest = %d\n", a, b);
    else if(b > a)
        printf("Largest = %d, Smallest = %d\n", b, a);
    else
        printf("Both are equal.\n");

    return 0;
}
