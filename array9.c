#include<stdio.h>
int main()
{
    int arr[5]={1,2,3,4,5},i,rev[5];

    for(i=0;i<5;i++)
    {
        rev[i]=arr[5-1-i];
    }
    printf("the reverse value\n");
    for(i=0;i<5;i++)
    {


        printf("%d",rev[i]); }

        return 0;

}
