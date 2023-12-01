#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define BUFF_SIZE 128

int main(int argc, char *argv[]) {
    unsigned int  num = 0;
    unsigned long sum = 0, i;
    char buff[BUFF_SIZE] = { 0 };

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open %s file: ", argv[1]);
        perror(NULL);
        return 1;
    }

    while (fgets(buff, BUFF_SIZE, fp)) {
        for (i = 0; i < strlen(buff); i++) {
            if (buff[i] >= 48 && buff[i] <= 57) {
                num *= 10;
                num += buff[i] - 48;
                break;
            }
        }

        for (i = strlen(buff); ; i--) {
            if (buff[i] >= 48 && buff[i] <= 57) {
                num *= 10;
                num += buff[i] - 48;
                break;
            }
        }

        sum += num;
        num = 0;
    }
    printf("Part 1: %lu\n", sum);

    fclose(fp);
    return 0;
}
