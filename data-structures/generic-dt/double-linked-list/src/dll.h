#ifndef GENERIC_DLL_H
#define GENERIC_DLL_H

#ifndef size_t
# define size_t unsigned long
#endif /* size_t */

#define DLL_DEINIT_END __attribute__((cleanup(dll_deinit)))

#define check_then_free(p) if ((p)) free((p))

#define is_null(p) (!(p))


typedef struct __val_t {
    void *data;
    size_t size;
} Value_t;


typedef struct __node_t {
    Value_t *val;
    struct __node_t *next;
    struct __node_t *prev;
} Node_t;


typedef struct __dll_t {
    Node_t *head;
    Node_t *tail;
} Dll_t;

Dll_t *dll_init();

void dll_deinit(Dll_t **dllp);

int dll_append(Dll_t *dllp, void *val, size_t val_size);

Node_t *dll_find(Dll_t *dllp, void *val);


#endif /* GENERIC_DLL_H */
