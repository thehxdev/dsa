#include <stdio.h>
#include <errno.h>

// bits count on each line
#define BIT_COUNT (12)
#define BUFF_SIZE (BIT_COUNT+2)

int main(int argc, char *argv[]) {
	char buff[BUFF_SIZE] = { 0 };
	int bits_frequescy[BIT_COUNT] = { 0 }, i, lines = 0;

	if (argc != 2) {
		printf("Usage: %s <input>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		perror("could not open input file");
		return errno;
	}

	while ((fgets(buff, BUFF_SIZE, fp)) != NULL) {
		for (i = 0; i < BIT_COUNT; i++)
			// just count ones
			bits_frequescy[i] += (buff[i] - '0');
		lines += 1;
	}
	fclose(fp);

	short gamma_rate = 0;
	short epsilon_rate = 0;
	for (i = 0; i < BIT_COUNT; i++) {
		gamma_rate |= ((bits_frequescy[i] > (lines/2)) << (BIT_COUNT-i-1));
	}
	epsilon_rate = ((~gamma_rate) & (0xfff));

	printf("Part 1: %d\n", gamma_rate * epsilon_rate);
	return 0;
}
