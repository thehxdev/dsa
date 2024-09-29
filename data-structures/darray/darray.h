#ifndef DSA_DARRAY_H
#define DSA_DARRAY_H

#define DA_DEFINE(struct_name, item_type)   \
    struct struct_name {                    \
        item_type *items;                   \
        size_t len;                         \
        size_t cap;                         \
    }

#define __DA_CAP_GROW_UNIT   (25)

#define __DA_ADD_CAP(da_ptr) ((da_ptr)->cap += __DA_CAP_GROW_UNIT)

/**
 * Default set-last-value macro. this macro sets last item the dynamic array to
 * a value pointed by `item_ptr`
 */
#define __DA_SET_LAST_VALUE(da_ptr, item_ptr) \
    memmove(&((da_ptr)->items[(da_ptr)->len]), (item_ptr), sizeof(*(da_ptr)->items))

#define __DA_APPEND_MANY_FN(da_ptr, items_ptr, count) \
    memmove(&((da_ptr)->items[(da_ptr)->len]), (items_ptr), (count) * sizeof(*(da_ptr)->items))

#define __DA_GROW_FN(da_ptr)                                            \
    do {                                                                \
        size_t __new_size__ = (da_ptr)->cap * sizeof(*(da_ptr)->items); \
        (da_ptr)->items = realloc((da_ptr)->items, __new_size__);       \
    } while (0)

/**
 * Grow dynamic array's items pointer
 */
#define DA_GROW(da_ptr)                     \
    if ((da_ptr)->len == (da_ptr)->cap) {   \
        __DA_ADD_CAP((da_ptr));             \
        __DA_GROW_FN((da_ptr));             \
    }

/**
 * Append many items with one shot
 *
 * `fn` is a macro or function that takes a pointer to a dynamic array and
 * a pointer to a values that you want to append and count of them, then
 * sets the last item in the list to that value.
 * like `__DA_APPEND_MANY_FN` macro defined above.
 */
#define DA_APPEND_MANY_C(da_ptr, items_ptr, count, fn)      \
    do {                                                    \
        while ((da_ptr)->len + (count) > (da_ptr)->cap) {   \
            __DA_ADD_CAP((da_ptr));                         \
        }                                                   \
        __DA_GROW_FN((da_ptr));                             \
        fn((da_ptr), (items_ptr), (count));                 \
        (da_ptr)->len += (count);                           \
    } while (0)

#define DA_APPEND_MANY(da_ptr, items_ptr, count)    \
    DA_APPEND_MANY_C((da_ptr), (items_ptr), (count), __DA_APPEND_MANY_FN)

/**
 * Customizable append macro
 *
 * `fn` is a macro or function that takes a pointer to a dynamic array and
 * a pointer to a value that you want to append, and sets the last item in the
 * list to that value. like `__DA_SET_LAST_VALUE` macro defined above.
 */
#define DA_APPEND_C(da_ptr, item_ptr, fn)   \
    do {                                    \
        DA_GROW((da_ptr));                  \
        if (!(da_ptr)->items)               \
            break;                          \
        fn((da_ptr), (item_ptr));           \
        (da_ptr)->len += 1;                 \
    } while (0)

#define DA_APPEND(da_ptr, item_ptr) \
    DA_APPEND_C((da_ptr), (item_ptr), __DA_SET_LAST_VALUE)

/**
 * foreach :D
 */
#define DA_FOREACH(da_ptr, var, proc)                       \
    do {                                                    \
        for (size_t __i = 0; __i < (da_ptr)->len; __i++) {  \
            var = &(da_ptr)->items[__i];                    \
            do {proc} while (0);                            \
        }                                                   \
    } while (0)

#define DA_GET(da_ptr, idx) \
    (assert((idx) >= 0), assert((idx) < (da_ptr)->len), &((da_ptr)->items[(idx)]))


#endif /* DSA_DARRAY_H */
