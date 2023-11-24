#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 32

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    char buff[BUFF_SIZE] = { 0 };
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open %s file\n", argv[1]);
        return 1;
    }

    int bits_frequency[12] = { 0 };
    while (fgets(buff, BUFF_SIZE, fp)) {
        for (uint32_t i = 0; i < strlen(buff); i++) {
            if (buff[i] == '1') {
                bits_frequency[i] += 1;
            } else {
                bits_frequency[i] -= 1;
            }
        }
    }

    uint16_t decimal_gamma = 0;
    uint16_t decimal_epsilon = 0;
    for (int i = 0; i < 12; i++) {
        if (bits_frequency[i] > 0)
            bits_frequency[i] = 1;
        else
            bits_frequency[i] = 0;
        decimal_gamma += (bits_frequency[i] * ((int) pow(2, 11 - i)));
    }
    decimal_epsilon = ((~decimal_gamma) & (0xfff));
    printf("Part 1: %d\n", decimal_gamma * decimal_epsilon);

    fclose(fp);
    return 0;
}
