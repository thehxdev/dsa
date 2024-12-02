#include <stdio.h>
#include <stdlib.h>

#define COUNT   (1000)
#define BUF_SIZE    (32)

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void sort_nums(int *arr, int len) {
    /* bubble sort */
    int i, j;
    for (i = len - 1; i > 0; i--)
        for (j = 0; j < i; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "failed to open file %s: ", argv[1]);
        perror(NULL);
        return 2;
    }

    int i;
    int *xs = malloc(sizeof(int) * COUNT * 2);
    if (!xs) {
        fprintf(stderr, "failed to allocate buffer for numbers");
        return 2;
    }
    for (i = 0; fscanf(fp, "%d%d", &xs[i], &xs[i+COUNT]) != EOF; i++);

    sort_nums(xs, COUNT);
    sort_nums(&xs[COUNT], COUNT);

    int sum = 0;
    for (i = 0; i < COUNT; i++)
        sum += abs(xs[i] - xs[i+COUNT]);

    printf("%d\n", sum);
    fclose(fp);
    return 0;
}
