#include<stdio.h>
int main()
{
    int a[10]={1,2,3,1,2,3,4,1,4,3},freq[100]={0},i;

    for(i=0;i<10;i++)
    {
        freq[a[i]]++;
    }
    for(i=0;i<10;i++)
    {


    if(freq[i]>0)
    {
        printf("the elements is%d and freq is%d\n",i,freq[i]);
    }
    }
    return 0;
}
