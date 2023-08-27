#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include "ht.h"


// static uint32_t power_to(uint32_t num, uint32_t p) {
//     uint32_t x = num;
//     for (uint32_t i = 1; i < p; i++)
//         x *= num;
//     return x;
// }

size_t ht_make_hash(const char *key) {
    size_t hash = 0x555555;
    int c;

    while ((c = *(key++))) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HT_CAPACITY;
}


// size_t ht_make_hash(const char *key) {
//     size_t alphabet_size = 36; // a - z & 0 - 9
//     size_t key_len = strlen(key);
// 
//     size_t alpha = power_to(alphabet_size, key_len);
// 
//     size_t sum = 0;
//     for (size_t i = 0; i < key_len; i++)
//         sum += (power_to(alphabet_size, (key_len + (i + 1)))) * key[i];
// 
//     return (alpha + sum) % (HT_CAPACITY);
// }


static bool ht_key_exists(HT *htp, const char *key) {
    for (size_t i = 0; i < htp->len; i++) {
        if (strcmp(htp->keys[i], key) == 0)
            return true;
    }
    return false;
}


HT *ht_new() {
    HT *nht = (HT*) malloc(sizeof(HT));
    if (nht == NULL)
        return nht;

    nht->len  = 0;
    return nht;
}


int ht_add(HT *htp, const char *key, void *val, size_t val_size) {
    if (ht_key_exists(htp, key))
        return 1;
    size_t idx = ht_make_hash(key);

    htp->vals[idx] = malloc(val_size);
    if (htp->vals[idx] == NULL) 
        return 2;
    memmove(htp->vals[idx], val, val_size);

    htp->keys[htp->len] = calloc(sizeof(char), strlen(key) + 1);
    if (htp->keys[htp->len] == NULL) {
        free(htp->vals[idx]);
        htp->vals[idx] = NULL;
        return 2;
    }
    strcpy(htp->keys[htp->len], key);

    htp->len += 1;
    return 0;
}


int ht_free(HT *htp, void (*fn) (void *p)) {
    if (htp == NULL)
        return 1;

    size_t hash = 0;
    for (size_t i = 0; i < htp->len; i++) {
        hash = ht_make_hash(htp->keys[i]);
        free(htp->keys[i]);
        fn(htp->vals[hash]);
        htp->vals[hash] = NULL;
    }

    free(htp);
    return 0;
}


void *ht_getval(HT *htp, const char *key) {
    if (!ht_key_exists(htp, key))
        return NULL;

    size_t idx = ht_make_hash(key);
    return htp->vals[idx];
}


int ht_change(HT *htp, const char *key, void *val, size_t val_size) {
    if (!ht_key_exists(htp, key))
        return 1;

    size_t idx = ht_make_hash(key);
    if (htp->vals[idx] == NULL)
        return 1;
    htp->vals[idx] = realloc(htp->vals[idx], val_size);
    memmove(htp->vals[idx], val, val_size);

    return 0;
}
