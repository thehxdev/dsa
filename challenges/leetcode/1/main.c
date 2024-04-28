#include <stdio.h>
#include <stdlib.h>


int* twoSum(int* nums, int numsSize, int target, int* returnSize);


int main(void) {
    /* one of the test cases */
    int nums[] = { 2, 7, 11, 15 };
    size_t nums_len = sizeof(nums) / sizeof(nums[0]);

    int *retsize = (int*) malloc(sizeof(int));
    *retsize = 0;

    int *result = twoSum(nums, nums_len, 9, retsize);
    if (result == NULL)
        return 1;

    printf("Result: [ %d, %d ]\n", result[0], result[1]); /* [0, 1] */

    free(result);
    return 0;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *res = (int*) calloc(sizeof(int), 2);
    if (res == NULL)
        return NULL;

    *returnSize = 2;

    for (int i = 0; i < numsSize; i += 1) {
        for (int j = i + 1; j < numsSize; j += 1) {
            if (nums[i] + nums[j] == target) {
                res[0] = i;
                res[1] = j;
                return res;
            }
        }
    }

    return res;
}
