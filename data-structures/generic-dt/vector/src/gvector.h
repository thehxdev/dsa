#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H


#ifndef size_t
# define size_t unsigned long
#endif /* size_t */

#define GVEC_DEF_CAP 20

#define DEINIT_GVEC __attribute__((cleanup(gvec_free)))

#define is_null(p) (!(p))

#define check_then_free(p) if ((p)) free((p))


typedef struct __val {
    void *data;
    size_t size;
} Val_t;


typedef struct __gvec {
    Val_t **vals;
    size_t len;
    size_t cap;
} GVec_t;


GVec_t *gvec_new(size_t cap);

void gvec_free(GVec_t **gvp);

int gvec_append(GVec_t *gvp, void *val, size_t val_size);

Val_t *gvec_pop(GVec_t *gvp);

void *gvec_get(GVec_t *gvp, size_t idx);

void val_free(Val_t **vp);

#endif /* GENERIC_VECTOR_H */
