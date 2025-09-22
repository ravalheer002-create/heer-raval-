#include<stdio.h>
int main()
{
    int a,arr[9]={500,200,5,50,20,10,5,2,1};
    printf("enter the value\n");
    scanf("%d",&a);
    for (int i=0;i<9;i++)
    {
      if(a>=arr[i])
      {
          int count=a/arr[i];
          printf("%d x %d\n",arr[i],count);
          a=a%arr[i];
      }
    }

    return 0 ;

}
