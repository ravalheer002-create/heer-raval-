#include <stdio.h>

int main() {
    int i;
    printf("First 10 even numbers:\n");
    for(i = 2; i <= 20; i += 2) {
        printf("%d ", i);
    }
    return 0;
}

