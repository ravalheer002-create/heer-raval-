#include <stdio.h>
int main() {
    int i, j;
    for(i = 1; i <= 3; i++) {
        for(j = 1; j <= 3; j++) {
            printf("%d %d %d\n", i, j, (i+j)/2);
        }
    }
    return 0;
}

