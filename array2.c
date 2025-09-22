#include <stdio.h>

int main() {
    int arr[10];   
    int i;

    
    printf("Enter 10 values:\n");
    for(i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    
    printf("\nThe 4th value is: %d", arr[3]);  
    printf("\nThe 7th value is: %d", arr[6]);  
    printf("\nThe 9th value is: %d", arr[8]);  

    return 0;
}
