#include <stdio.h>

int main() {
    int arr[5];   // declare array of size 5
    int i;

    // Input 5 values
    printf("Enter 5 values:\n");
    for(i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }

    // Print the values
    printf("\nThe values you entered are:\n");
    for(i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
