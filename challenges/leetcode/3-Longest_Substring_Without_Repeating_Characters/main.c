#include <stdio.h>


///////////////////////////////////
/// Solution
///////////////////////////////////

int substringUncommonLen(char **base, char **curr) {
    int len = *curr - *base;
    char *tbase = *base;
    char *tcurr = *curr;
    while (tbase != tcurr) {
        if (*tbase == *tcurr) {
            *curr = (*base) += 1;
            break;
        }
        tbase += 1;
    }
    return len;
}

int lengthOfLongestSubstring(char* s) {
    int maxLen = 0, currLen = 0;
    char *base = s, *curr = s;

    while (1) {
        currLen = substringUncommonLen(&base, &curr);
        if (currLen > maxLen)
            maxLen = currLen;

        if (*curr == '\0')
            break;
        curr += 1;
    }

    return maxLen;
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
    printf("%d\n", lengthOfLongestSubstring(s));
    return 0;
}
