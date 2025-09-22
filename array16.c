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
    printf("where you want to delete the number\n");
    scanf("%d",&p);


    for(i=p-1;i<n-1;i++)
    {
     a[i]=a[i+1];
    }


    n--;
        printf("Array after insertion:\n");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}





