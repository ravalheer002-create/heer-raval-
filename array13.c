#include<stdio.h>
int main()
{
    int a[10],i,n,num,p;

    printf("enter the number of elements\n");
    scanf("%d",&n);

    printf("enter the elements\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("where you want to insert the number\n");
    scanf("%d",&p);
    printf("enter the number to insert at ");
    scanf("%d",&num);

    for(i=n;i>=p;i--)
    {
     a[i]=a[i-1];
    }

    a[p-1]=num;
    n++;
        printf("Array after insertion:\n");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}




