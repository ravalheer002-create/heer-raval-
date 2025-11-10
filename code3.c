#include <stdio.h>

int main() {
    int a[3][3], *p, i, j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            scanf("%d",&a[i][j]);
    p = &a[0][0];
    int max=*p, min=*p;
    for(i=0;i<9;i++,p++){
        if(*p>max) max=*p;
        if(*p<min) min=*p;
    }
    printf("Largest=%d Smallest=%d",max,min);
    return 0;
}

