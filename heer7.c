#include <stdio.h>

int main() {
    int minutes, hours, remaining;
    printf("Enter minutes: ");
    scanf("%d", &minutes);

    hours = minutes / 60;
    remaining = minutes % 60;

    printf("%d minutes = %d hours and %d minutes\n", minutes, hours, remaining);
    return 0;
}
