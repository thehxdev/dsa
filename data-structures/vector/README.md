# Vector

A **generic** implementation of vector (Dynamic Array) data structure.

This vector can hold multiple data types at one time but some functions like `vec_print` will not
work properly because `printf` function needs format specifiers.

If You want to store multiple data types at once in one vector, set vector type to `VOID_T` when initializing or
creating new vector.



## Macros

#### `cuint64`

A short form of `const u_int64_t` type. Used for functions that require an index for their job.


#### `BYTES_OF_VOID`

Calculate bytes of memory for `void **` data type. Used for `malloc`, `realloc` and `calloc`.


#### `BYTES_OF_VECTOR`

Calculate bytes of memory for `vector_t` data type. Used for `malloc`, `realloc` and `calloc`.


#### `VTOI`

Convert a void pointer of `int64_t` data type to it's actual value.


#### `VTOCH`

Convert a void pointer of `char` data type to it's actual value.

#### `VTOS`

Convert a void pointer of `char *` data type (string) to it's actual value.


#### `INT64_T`, `CHAR_T`, `STR_T` and `VOID_T`

Macros to specify vector's type. `VOID_T` used for custom or other data types.



## Vector Methods

#### `vec_new`

Creates a new `vector_t` instance and returns it.
You must initialize your vector befor using it or passing it to other fuctions.

- Args:
    - `u_int8_t`: vector type

- Ret: 
    - `vector_t`: a new `vector_t` instance

```c
/* Create a vector with void (not specified) type */
vector_t myVec = vec_new(VOID_T);
```


#### `vecptr_init`
Initialize a vector pointer that allocated by malloc.
**This function wipes vector's content.**

- Args:
    - `vector_t *vec`: pointer to a vector
    - `u_int8_t`: vector type

- Ret: `void`


#### `vec_append`

Append a new value to vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `void *val`: pointer to a value

- Ret:
    - `u_int8_t`: 0 if no errors, 1 if an error occures

```c
vec_append(&myVec, 50) /* if vector type is INT64_T */

vec_append(&myVec, 'a') /* if vector type is CHAR_T */

vec_append(&myVec, "Hello") /* if vector type is STR_T */
```


#### `vec_get`

Get a value's void pointer that stored at a specific index in the vector.
Scince this function returns a void pointer, you must do a type casting
befor assingning the return value to a specific variable.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const int64_t idx`: value index

- Ret:
    - If no errors `void *`
    - If error (index out of range) -> No return, exit program.

```c
/* get first (0 index) element in the vector */
vec_get(&myVec, 0);
```


#### `vec_pop`


Remove an element at the end of the vector and return it's void pointer.

- Args:
    - `vector_t *vec`:pointer to a vector

- Ret:
    - `void *`:void pointer to a value



#### `vec_delete`

Free up a vector's content that allocated on the heap.
**If vector contains __elements__ that allocated on the heap,
it's your responsibility to free them before calling this function.**

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_delete(&myVec);
```


#### `vec_clean`

Free up a vector's content and initialize it again.
**If vector contains __elements__ that allocated on the heap,
it's your responsibility to free them before calling this function.**

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

Print elements of a vector to `stdout`. Only supported for `INT64_T`, `CHAR_T` and `STR_T` types.
If vector type is `VOID_T` prints it's address.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret: `void`

```c
vec_print(&myVec);
```


#### `vec_sum`

Calculate sum of elements in the vector. only for `INT64_t` data type.

- Args:
    - `vector_t *vec`: pointer to a vector

- Ret:
    - `int64_t`: sum of elements

```c
int64_t sum_of_vec = vec_sum(&myVec);
```


#### `vec_set`

Update an element to a new value. If given `idx` (index) is out of range, do nothing.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t idx`: index of element
    - `vecT val`: new value

- Ret: `void`

```c
/* 
 * change first element content to 10
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
**Not working for `VOID_T` data type.**

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

Sort the vector with `quick-sort` algorithm.
**Only works for `INT64_T` data type.**

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t lower`: lower bound of vector
    - `const u_int64_t upper`: upper bound of vector

- Ret: `void`

```c
/* Sort entire vector */
vec_sort(&myVec, 0, (myVec.length - 1));
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

Inster a value to a specific index in the vector.

- Args:
    - `vector_t *vec`: pointer to a vector
    - `const u_int64_t idx`: index to add element
    - `void *val`: pointer to a value

- Ret: `void`

```c
/* Insert number 5 to index 1 */
vec_insert(&myVec, 1, 5);
```

