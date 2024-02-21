#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFF_SIZE 1024

char *extrac_num(char *s, char **s_ptr);
long process_line_p1(const char *line);


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Opening input file failed: ");
        perror(NULL);
        return 1;
    }

    long p1 = 0;
    char buff[BUFF_SIZE];
    while (fgets(buff, BUFF_SIZE, fp))
        p1 += process_line_p1(buff);

    printf("Part 1: %ld\n", p1);
    fclose(fp);
    return 0;
}


/* an iterator to extract a number on each call 
 * (inspired by `strtok` function in string.h) */
char *extrac_num(char *s, char **s_ptr) {
    char c, *end;

    if (s == NULL)
        s = *s_ptr;

    while ((c = *s)) {
        if (c >= '0' && c <= '9' )
            break;
        s++;
    }
    if (*s == '\0') {
        *s_ptr = s;
        return NULL;
    }

    end = s+1;
    while ((c = *end)) {
        if (c < '0' || c > '9')
            break;
        end++;
    }
    if (*end == '\0') {
        **s_ptr = '\0';
        return s;
    }

    *end = '\0';
    *s_ptr = end + 1;
    return s;
}


long process_line_p1(const char *line) {
    long num, max = -1, min = LONG_MAX;
    char *tmp = (char*)line, *s_ptr;

    char *t = extrac_num(tmp, &s_ptr);
    while (t) {
        num = atoi(t);
        printf("Num = %ld\n", num);
        if (num > max)
            max = num;
        if (num < min)
            min = num;
        t = extrac_num(NULL, &s_ptr);
    }

    printf("Min = %ld | Max = %ld\n", min, max);
    return max - min;
}
