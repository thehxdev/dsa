#include <stdio.h>


///////////////////////////////////
/// Solution
///////////////////////////////////

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int removeElement(int *nums, int numsSize, int val) {
    int i, j;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == val) {
            for (j = i+1; j < numsSize; j++)
                swap(&nums[j-1], &nums[j]);
            i -= 1;
            numsSize -= 1;
            if (i == numsSize)
                break;
        }
    }
    return numsSize;
}


///////////////////////////////////
/// Test
///////////////////////////////////


int main(void) {
    int i, res;
    int nums[] = { 0, 1, 2, 2, 3, 0, 4, 2 };
    int len = sizeof(nums) / sizeof(nums[0]);

    res = removeElement(nums, len, 2);
    for (i = 0; i < res; i++)
        printf("%d ", nums[i]);
    return 0;
}
