# Vector (Not Updated for new version)

A vector (Dynamic array) implementation that works with `int64_t`, `char` and also `char *` or string data types.

## Macros

#### `vecTnum`

Used to specify the `vecT` macro. I used 2 macros for vector type because I can compare `vecTnum` with numbers
to specify vector type.

You define this macro once and you can't change it later. This meanse the vector can hold one data type at the time.

- `vecTnum` valid numbers:
    - `0` -> `int64_t`
    - `1` -> `char`
    - `2` -> `char *` (string)

```c
#define vecTnum 0 /* for int64_t type */
#include "vector.h"
```

#### `vecT`

Defines the vector's content type.
Supported types:

- `int64_t`
- `char`
- `char *` (string)


## Vector Methods

#### `vec_new`

Creates a new `vector_t` instance and returns it.
You must initialize your vector befor using it or passing it to another fuctions.

- Args: `void`
- Ret: `vector_t`: a new `vector_t` instance

```c
vector_t myVec = vec_new();
```


#### `vec_append`

Append a new value to vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `vecT val`: new value with type `vecT`

- Ret: `void`

```c
vec_append(&myVec, 50) /* if vecTnum is 0 */

vec_append(&myVec, 'a') /* if vecTnum is 1 */

vec_append(&myVec, "Hello") /* if vecTnum is 2 */
```


#### `vec_get`

Get the value stored at a specific index in the vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const int64_t idx`: value index

- Ret:
    - If no errors `vecT`
    - If error (index out of range) -> No return, exit program.

```c
/* get first (0 index) element in the vector */
vec_get(&myVec, 0);
```


#### `vec_delete`

Free up a vector's content that allocated on the heap.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_delete(&myVec);
```


#### `vec_clean`

Free up a vector's content and initialize it again.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_clean(&myVec);
```


#### `vec_swap`

Swap 2 elements in the vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t idx1`: first element index
    - `const u_int64_t idx2`: second element index

- Ret: `void`

```c
/* swap first and second element */
vec_swap(&myVec, 0, 1);
```


#### `vec_print`

Print elements of a vector to `stdout`.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_print(&myVec);
```


#### `vec_sum`

If `vecTnum` is **NOT** equal to `2` (it's not string) calculate sum of elements in the vector.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret:
    - `int64_t`: sum of elements

```c
int64_t sum_of_vec = vec_sum(&myVec);
```


#### `vec_set`

Change an existing element's value to a new value. If given `idx` (index) is out of range, do nothing.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t idx`: index of element
    - `vecT val`: new value

- Ret: `void`

```c
/* 
 * change first element content to 10
 * (if vecTnum is 0)
 */
vec_set(&myVec, 0, 10);
```


#### `vec_reverse`

Reverse a vector.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_reverse(&myVec);
```


#### `vec_find`

Search for a specific value in vector and return it's index if found, if it's not return `-1`.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `vecT val`: value to search for

- Ret:
    - if found -> `int64_t`: index of value
    - if not found -> `-1`


```c
/* try to find number 1 in vector */
vec_find(&myVec, 1);
```


#### `vec_sort`

if `vecTnum` is not 2, sort the vector with `quick-sort` algorithm.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t lower`: lower bound of vector
    - `const u_int64_t upper`: upper bound of vector

- Ret: `void`

```c
/* Sort entire vector */
vec_sort(&myVec, 0, myVec.length);
```


#### `vec_cpy`

Copy a vector to another vector.
**This function will wipe destination vector.**

- Args:
    - `vector_t *dest`: pointer to destination vector
    - `vector_t *src`: pointer to source vector

- Ret: `void`

```c
vec_sort(&destVec, &srcVec);
```


#### `vec_insert`

**Currently only for vecTnum 0 and 1.**

Inster a value to a specific index in the vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t idx`: index to add element
    - `vecT`: value

- Ret: `void`

```c
/* Insert number 5 to index 1 */
vec_insert(&myVec, 1, 5);
```

