#include <stdio.h>

int main() {
    long long bytes;
    printf("Enter bytes: ");
    scanf("%lld", &bytes);

    double KB = bytes / 1024.0;
    double MB = KB / 1024.0;
    double GB = MB / 1024.0;

    printf("%lld bytes = %.2f KB = %.2f MB = %.2f GB\n", bytes, KB, MB, GB);
    return 0;
}

