#include<stdio.h>
int main ()
{
    int A[10][10], B[10][10];
    int i, j, m, n;

    printf("Enter rows and columns of matrix: ");
    scanf("%d %d", &m, &n);
    printf("Enter elements of the matrix:\n");
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }


    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            B[j][i] = A[i][j];
        }
    }


    printf("Transpose of the matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}
