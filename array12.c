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
    printf("enter the number to insert at beginning");
    scanf("%d",&num);

    for(i=n;i>0;i--)
    {
     a[i]=a[i-1];
    }

    a[0]=num;
    n++;
        printf("Array after insertion:\n");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}



