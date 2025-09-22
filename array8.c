#include<stdio.h>
int main()
{
    int a[5], b[10];
    int skip, i, j = 0;
    printf("Enter 5 elements:\n");
    for(i = 0; i < 5; i++) {
        scanf("%d", &a[i]);
    }


    printf("Enter the value you want to skip: ");
    scanf("%d", &skip);
    for(i = 0; i < 5; i++) {
        if(a[i] == skip) {
            b[j] = 0;
        } else {
            b[j] = a[i];
        }
        j++;
    }


    for(; j < 10; j++) {
        b[j] = 0;
    }

    printf("This is result:\n");
    for(i = 0; i < 10; i++) {
        printf("%d ", b[i]);
    }

    return 0;
}
