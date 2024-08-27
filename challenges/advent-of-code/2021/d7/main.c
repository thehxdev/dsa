#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

typedef struct {
	int *ptr;
	int len;
	int cap;
} IntList;

IntList read_nums(FILE*);
long calculate_distances_sum(IntList, int);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <input>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		perror("could not open input file");
		return errno;
	}

	IntList list = read_nums(fp);
	fclose(fp);

	long min = LONG_MAX, i, distances_sum;
	for (i = 100; i < 500; i++) {
		distances_sum = calculate_distances_sum(list, i);
		if (min > distances_sum)
			min = distances_sum;
	}
	printf("Part 1: %ld\n", min);

	return 0;
}

IntList read_nums(FILE *fp) {
	// just to keep things simple, count the numbers first. (without dynamic arrays)
	char ch;
	IntList list = { NULL, 0, 50 };
	int count = 1, num = 0;
	while ((ch = fgetc(fp)) != EOF)
		if (ch == ',')
			count++;
	rewind(fp);


	list.ptr = (int*) malloc(count * sizeof(int));

	// parse all numbers in input file
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == ',' || ch == '\n') {
			list.ptr[list.len] = num;
			list.len++;
			num = 0;
			continue;
		}

		num *= 10;
		num += (ch - '0');
	}

	return list;
}

long calculate_distances_sum(IntList list, int base_line) {
	long sum = 0, delta;
	int *nums = list.ptr, i;

	for (i = 0; i < list.len; i++) {
		delta = nums[i] - base_line;
		sum += (delta < 0) ? ((-1) * delta) : delta;
	}

	return sum;
}
