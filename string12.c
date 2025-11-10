#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];
    int i, a = 0, e = 0, I = 0, o = 0, u = 0;

    printf("Enter a string: ");
    gets(str);

    for(i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if(ch == 'a') a++;
        else if(ch == 'e') e++;
        else if(ch == 'i') I++;
        else if(ch == 'o') o++;
        else if(ch == 'u') u++;
    }

    printf("Frequency of vowels:\n");
    printf("a = %d\n", a);
    printf("e = %d\n", e);
    printf("i = %d\n", I);
    printf("o = %d\n", o);
    printf("u = %d\n", u);

    return 0;
}

