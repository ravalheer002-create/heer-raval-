#include <stdio.h>
int main() {
    int i, j;
    for(j = 1; j <= 2; j++) {
        for(i = 1; i <= 3; i++) {
            printf("%d %d\n", i, j);
        }
    }
    return 0;
}

