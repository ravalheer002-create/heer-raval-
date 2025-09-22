#include <stdio.h>

int main() {
    int n, i, value, found = 0;


    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];


    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }


    printf("Enter the value to search: ");
    scanf("%d", &value);


    for(i = 0; i < n; i++) {
        if(arr[i] == value) {
            printf("Value %d found at position %d.\n", value, i + 1);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Value %d not found in the array.\n", value);
    }

    return 0;
}

