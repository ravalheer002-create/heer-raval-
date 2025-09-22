#include<stdio.h>


    int main() {
    int A[10][10], B[10][10], C[10][10];
    int i, j, k, m, n, p, q;


    printf("Enter rows and columns of first matrix:\n");
    scanf("%d %d", &m, &n);

    printf("Enter rows and columns of second matrix:\n");
    scanf("%d %d", &p, &q);

    if(n!=p)
    {
        printf("the matrix multiplication is not possible\n");
    }
else
{
    printf("enter the 1st matrix\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            scanf("%d\n",&A[i][j]);
    }
    printf("enter the 2nd matrix\n");
    for(i=0;i<p;i++)
    {
        for(j=0;j<q;j++)
            scanf("%d\n",&B[i][j]);
    }
    printf("the  matrix\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<q;j++)
            scanf("%d\n",&C[i][j]);
    }

    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<p;k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }

    }
}
printf("the result is %d\n",C[i][j]);
return 0;
}
