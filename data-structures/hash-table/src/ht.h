/*
 * WARNING!
 * This is a Hash-Table implementation with a simple
 * Hash function. So key collisions are possible.
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include "dll.h"

#define HT_CAPACITY (1 << 16)

typedef struct __ht {
    void *vals[HT_CAPACITY];
    DLL *keys;
    size_t len;
} HT;


/**
 * Generate hash (index) from a key
 *
 * @key: key string
 *
 * @ret: index (hash)
 */
size_t ht_make_hash(const char *key);


/**
 * @WARN!
 * Create a new Hash-Table
 *
 * @ret: pointer to new HT | NULL
 */
HT *ht_new();


/**
 * Add a new value to Hash-Table
 *
 * @htp: pointer to a HT
 * @key: key of value
 * @val: pointer to value
 * @val_size: sizeof `val` in bytes
 *
 * @ret: 0 ok | 1 key exist | 2 error
 */
int ht_add(HT *htp, const char *key, void *val, size_t val_size);


/**
 * Free a HT from memorty including it's values
 *
 * @htp: pointer to a HT
 * @fn: a function pointer to free a value
 *
 * @ret: 0 ok | 1 error
 */
int ht_free(HT *htp, void (*fn) (void *p));


/**
 * @WARN!
 * Get value of a key in HT
 *
 * @htp: pointer to a HT
 * @key: key string
 *
 * @ret: pointer to value | NULL
 */
void *ht_getval(HT *htp, const char *key);


/**
 * Change a key's value in HT
 *
 * @htp: pointer to a HT
 * @key: key of value
 * @val: pointer to new value
 * @val_size: sizeof `val` in bytes
 *
 * @ret: 0 ok | 1 error
 */
int ht_change(HT *htp, const char *key, void *val, size_t val_size);


/**
 * Delete a value from HT
 *
 * @htp: pointer to a HT
 * @key: key of value
 * @fn: a function pointer to free a value
 *
 * @ret: 0 ok | 1 error
 */
int ht_remove(HT *htp, const char *key, void (*fn) (void *p));

#endif // HASH_TABLE_H
