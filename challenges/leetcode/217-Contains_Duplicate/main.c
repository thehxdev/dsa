#include <stdio.h>
#include <stdbool.h>

#define size 10

// O(n^2)
bool containsDuplicate(int* nums, int numsSize) {
    int i, j, curr;
    for (i = 0; i < numsSize; i++) {
        curr = nums[i];
        for (j = i+1; j < numsSize; j++)
            if (curr == nums[j])
                return true;
    }
    return false;
}


int main(void) {
    int nums[size] = { 84, 12, 1, 655, 78, 1, 9, 43, 8723, 10 };
    bool ans = containsDuplicate(nums, size);
    printf("%d\n", ans);
    return 0;
}
