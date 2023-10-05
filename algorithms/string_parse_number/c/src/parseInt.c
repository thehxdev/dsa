/**
 * Parse numbers in ascii character strings algorithm
 */

#include <string.h>
#include <math.h>
#include "parseInt.h"

static int charToInt(const char _c) {
    return ((int) _c) - 48;
}


static int firstNumIdx(const char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            return i;
        }
    }

    return -1;
}


static int lastNumIdx(const char *str) {
    unsigned int i = 0;
    for (; i < strlen(str); i++) {
        if (str[i] < 48 || str[i] > 57) {
            return (i == 0) ? 0 : i - 1;
        }
    }
    return i - 1;
}


extern int parseInt(const char *str) {
    int firstNum, lastNum;

    firstNum = firstNumIdx(str);
    if (firstNum == -1) {
        return 0;
    }
    lastNum = lastNumIdx((str + firstNum)) + firstNum;

    int result = 0;
    for (int i = lastNum; i >= firstNum; i--) {
        result += (charToInt(str[i]) * pow(10, (lastNum - i)));
    }

    return result;
}
