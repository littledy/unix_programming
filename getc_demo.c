#include <stdio.h>

int main() {
    int c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    // ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');
    ungetc(c, stdin);
    c = getchar();
    putchar(c);
    putchar('\n');

    return 0;
}