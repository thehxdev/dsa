#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include "dll.h"
#include "ht.h"


// size_t ht_make_hash(const char *key) {
//     size_t hash = 0x555555;
//     int c;
//
//     while ((c = *(key++))) {
//         hash = ((hash << 5) + hash) + c;
//     }
//
//     return hash % HT_CAPACITY;
// }


uint64_t ht_make_hash(const char *key) {
    uint64_t alphabet_size = 36; // a - z & 0 - 9
    uint64_t key_len = strlen(key);
    uint64_t alpha = alphabet_size ^ key_len;

    uint64_t num = 0;
    for (uint64_t i = 0; i < key_len; i++)
        num = ((alphabet_size * (key_len + key[i])) * key[i]) % HT_CAPACITY;

    return (alpha + num + key_len) % HT_CAPACITY;
}


HT *ht_new() {
    HT *nht = (HT*) malloc(sizeof(HT));
    if (nht == NULL)
        return nht;

    nht->keys = dll_new(HT_CAPACITY);
    nht->len  = 0;
    return nht;
}


int ht_add(HT *htp, const char *key, void *val, size_t val_size) {
    if (dll_findby_key(htp->keys, key))
        return 1;
    size_t idx = ht_make_hash(key);

    htp->vals[idx] = malloc(val_size);
    if (htp->vals[idx] == NULL) 
        return 2;
    memmove(htp->vals[idx], val, val_size);

    dll_add_key(htp->keys, key);
    htp->len += 1;
    return 0;
}


int ht_free(HT *htp, void (*fn) (void *p)) {
    if (htp == NULL)
        return 1;

    uint64_t hash = 0;
    Node *tmp = htp->keys->head;
    if (tmp == NULL)
        goto ret;

    Node *next = tmp->next;
    while (1) {
        hash = ht_make_hash(tmp->key);
        fn((void*)htp->vals[hash]);
        node_free(tmp);
        tmp = next;
        if (tmp == NULL)
            break;
        next = tmp->next;
    }

ret:
    free(htp);
    return 0;
}


void *ht_getval(HT *htp, const char *key) {
    if (!dll_findby_key(htp->keys, key))
        return NULL;

    size_t idx = ht_make_hash(key);
    return htp->vals[idx];
}


int ht_change(HT *htp, const char *key, void *val, size_t val_size) {
    if (!dll_findby_key(htp->keys, key))
        return 1;

    size_t idx = ht_make_hash(key);
    if (htp->vals[idx] == NULL)
        return 1;
    htp->vals[idx] = realloc(htp->vals[idx], val_size);
    memmove(htp->vals[idx], val, val_size);

    return 0;
}


int ht_remove(HT *htp, const char *key, void (*fn) (void *p)) {
    Node *tmp = dll_findby_key(htp->keys, key);
    if (tmp == NULL)
        return 1;

    size_t idx = ht_make_hash(tmp->key);
    fn((void*)htp->vals[idx]);
    dll_remove_node(htp->keys, tmp);
    htp->len -= 1;
    return 0;
}
