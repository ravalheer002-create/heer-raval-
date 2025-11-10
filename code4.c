#include <stdio.h>

int main() {
    char books[3][50];
    char *p[3];
    for(int i=0;i<3;i++){
        printf("Enter book %d: ",i+1);
        gets(books[i]);
        p[i]=books[i];
    }
    printf("\nBook names:\n");
    for(int i=0;i<3;i++)
        puts(p[i]);
    return 0;
}

