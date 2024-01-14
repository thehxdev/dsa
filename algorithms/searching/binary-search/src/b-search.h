#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#ifndef size_t
# define size_t unsigned long
#endif /* size_t */

/* use a simple sorting algorithm to sort the array */
void bubble_sort(int *arr, size_t len);

int *binary_search(int *arr, size_t len, int num);


#endif /* BINARY_SEARCH_H */
