#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#ifndef size_t
# define size_t unsigned long
#endif /* size_t */

void swap(int *x, int *y);

void bubble_sort(int *arr, size_t len);


#endif /* BUBBLE_SORT_H */
