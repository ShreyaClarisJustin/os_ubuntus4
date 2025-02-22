#include <stdio.h>
#include <ctype.h>

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    //to_uppercase(str);
//toupper((unsigned char) c);
	char s=str.toupper();
    printf("Uppercase string: %s\n",str);
    return 0;
}
