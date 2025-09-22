#include <stdio.h>

int main() {
    int arr[10], result[10];
    int i, n, choice;


    printf("Enter 10 elements:\n");
    for(i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }


    printf("Enter number of positions to shift: ");
    scanf("%d", &n);


    printf("Enter 1 for Left Shift, 2 for Right Shift: ");
    scanf("%d", &choice);


    for(i = 0; i < 10; i++) {
        result[i] = 0;
    }

    if(choice == 1) {
        for(i = 0; i < 10; i++) {
            if(i + n < 10) {
                result[i] = arr[i + n];
            }
        }
    }
    else if(choice == 2) {
        for(i = 0; i < 10; i++) {
            if(i - n >= 0) {
                result[i] = arr[i - n];
            }
        }
    }
    else {
        printf("Invalid choice!");
        return 0;
    }


    printf("Resultant Array:\n");
    for(i = 0; i < 10; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}

