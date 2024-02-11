#include <stdio.h>
#include <stdlib.h>

#define xfree(p) do { free((p)); (p) = NULL; } while(0)
void readFile(FILE *fp, char **buff, long *buff_len);
char getBuffChar(char *buff, long len, long idx);
long solvePart1(char *buff, long len);
long solvePart2(char *buff, long len);


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    long len, p1, p2;
    char *buff = NULL;
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open \'%s\' file: ", argv[1]);
        perror(NULL);
        return 1;
    }
    readFile(fp, &buff, &len);

    p1 = solvePart1(buff, len);
    p2 = solvePart2(buff, len);

    printf("Part 1 = %ld\n", p1);
    printf("Part 2 = %ld\n", p2);
    xfree(buff);
    fclose(fp);
    return 0;
}



void readFile(FILE *fp, char **buff, long *buff_len) {
    long f_size;

    fseek(fp, SEEK_SET, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    (*buff) = (char*) calloc(f_size, sizeof(char));
    if (!(*buff))
        return;
    fread(*buff, sizeof(char), f_size, fp);
    // don't include '\0' in length
    *buff_len = f_size-1;
}


char getBuffChar(char *buff, long len, long idx) {
    return buff[(idx%len)];
}


long solvePart1(char *buff, long len) {
    long i, sum = 0;
    char  curr, next;
    for (i = 0; i < len; i++) {
        curr = getBuffChar(buff, len, i);
        next = getBuffChar(buff, len, i+1);
        if (curr == next)
            sum += (curr - 48);
    }
    return sum;
}


long solvePart2(char *buff, long len) {
    char curr, next;
    long sum = 0, i, next_idx_step = len / 2;
    for (i = 0; i < len; i++) {
        curr = getBuffChar(buff, len, i);
        next = getBuffChar(buff, len, i+next_idx_step);
        if (curr == next)
            sum += (curr - 48);
    }
    return sum;
}
