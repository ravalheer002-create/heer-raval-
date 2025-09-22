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

    printf("enter the value you want to del\n");
    scanf("%d",&num);
    for(i=0;i<n;i++)
    {
     if(a[i]==num){
        p=i;
        break;
    }
    }



    for(i=p;i<n-1;i++)
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





