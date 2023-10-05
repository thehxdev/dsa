/**
 * Parse numbers in ascii character strings algorithm
 */

#include <string.h>
#include <math.h>
#include "parseInt.h"

static int charToInt(const char _c) {
    return ((int) _c) - 48;
}


static int firstNumIdx(const char *_s) {
    for (unsigned int i = 0; i < strlen(_s); i++) {
        if (_s[i] >= 48 && _s[i] <= 57) {
            return i;
        }
    }

    return -1;
}


static int lastNumIdx(const char *_s) {
    unsigned int i = 0;
    for (; i < strlen(_s); i++) {
        if (_s[i] < 48 || _s[i] > 57) {
            return (i == 0) ? 0 : i - 1;
        }
    }
    return i - 1;
}


extern int parseInt(const char *_s) {
    int firstNum, lastNum;

    firstNum = firstNumIdx(_s);
    if (firstNum == -1) {
        return 0;
    }
    lastNum = lastNumIdx((_s + firstNum)) + firstNum;

    int result = 0;
    for (int i = lastNum; i >= firstNum; i--) {
        result += (charToInt(_s[i]) * pow(10, (lastNum - i)));
    }

    return result;
}
