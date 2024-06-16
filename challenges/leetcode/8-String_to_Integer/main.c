#include <stdio.h>
#include <limits.h>

///////////////////////////////////
/// Solution
///////////////////////////////////

#define isDigit(ch) (((ch) >= '0') && ((ch) <= '9'))
#define charToDigit(ch) ((ch) - '0')


int myAtoi(char* s) {
    int num = 0, digit = 0;
    char neg = 0;

    while (*s == ' ') s += 1;

    switch (*s) {
        case '-':
            neg = 1;
        case '+':
            s += 1;
    }

    while (isDigit(*s)) {
        digit = charToDigit(*s);
        if (num > (INT_MAX / 10) || (num == (INT_MAX / 10) && digit > 7))
            return ((neg) ? INT_MIN : INT_MAX);

        num = (num * 10) + digit;
        s += 1;
    }

    return ((neg) ? (num * (-1)) : num);
}


///////////////////////////////////
/// Test
///////////////////////////////////

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *s = argv[1];
    printf("%d\n", myAtoi(s));
    return 0;
}
