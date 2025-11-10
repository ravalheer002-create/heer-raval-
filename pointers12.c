
#include <stdio.h>

int main() {
    char *arr[] = {"C", "Pointers", "Programming", "Language"};
    char **ptr = arr;

    printf("Third string: %s", *(ptr + 2));
    return 0;
}
