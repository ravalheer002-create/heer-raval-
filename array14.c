#include<stdio.h>
int main()
{
    int a[10],i,n,num;

    printf("enter the number of elements\n");
    scanf("%d",&n);

    printf("enter the elements\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("enter the number to insert at last\n");
    scanf("%d",&num);

    for(i=0;i<n;i++)
    {
     a[i];
    }

    a[n]=num;
    n++;
        printf("Array after insertion:\n");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}




