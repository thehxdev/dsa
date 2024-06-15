#include <stdio.h>
#include <limits.h>

///////////////////////////////////
/// Solution
///////////////////////////////////

#define isDigit(ch) (((ch) >= '0') && ((ch) <= '9'))
#define charToDigit(ch) ((ch) - '0')


int myAtoi(char* s) {
    char neg = 0;
    // FIXME: Just a temporarly solution.
    // I dont like this solution because it will fail in 32-bit machines.
    // I used a 64-bit number to catch a 32-bit number overflow.
    long num = 0;

    while (*s == ' ') s += 1;

    switch (*s) {
        case '-':
            neg = 1;
        case '+':
            s += 1;
    }

    while (isDigit(*s)) {
        num = (num * 10) + charToDigit(*s);
        if (num > INT_MAX)
            num = (neg) ? INT_MIN : INT_MAX;
        else if (num < INT_MIN)
            num = INT_MIN;
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
