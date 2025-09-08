
#include <stdio.h>

int main() {
    int m1, m2, m3, total;
    float avg;

    printf("Enter marks of 3 subjects: ");
    scanf("%d %d %d", &m1, &m2, &m3);

    if(m1 < 35 || m2 < 35 || m3 < 35) {
        printf("Fail (Less than 35 in a subject)\n");
    } else {
        total = m1 + m2 + m3;
        avg = total / 3.0;

        printf("Total = %d, Average = %.2f\n", total, avg);

        if(avg >= 70)
            printf("Grade: Distinction\n");
        else if(avg >= 60)
            printf("Grade: First Class\n");
        else if(avg >= 50)
            printf("Grade: Second Class\n");
        else if(avg >= 35)
            printf("Grade: Third Class\n");
        else
            printf("Fail\n");
    }

    return 0;
}
