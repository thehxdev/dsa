#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////
/// Solution
///////////////////////////////////

#define xfree(p) do { free((p)); (p) = NULL; } while (0)

// slice
typedef struct _slice {
    const char *ptr;
    size_t len;
} Slice;

typedef struct __node {
    Slice data;
    struct __node *next;
    struct __node *prev;
} Node;

typedef struct __path_stk {
    Node *first;
    Node *last;
    size_t len;
} PathStack;

// create new stack node
Node *node_new(const char *data, const size_t len) {
    if (len == 0)
        return NULL;

    Node *n = (Node*) malloc(sizeof(*n));
    *n = (Node){
        .data = (Slice){
            .ptr = data,
            .len = len,
        },
        .next = NULL,
        .prev = NULL,
    };

    return n;
}

void stk_push(PathStack *ps, Node *n) {
    if (!n)
        return;

    if (!ps->first) {
        ps->first = ps->last = n;
    } else {
        n->prev = ps->last;
        ps->last->next = n;
        ps->last = n;
    }

    ps->len += n->data.len;
}

void stk_pop(PathStack *ps) {
    Node *last = ps->last;

    if (!last->prev)
        return;

    if (last->prev) {
        last->prev->next = NULL;
        ps->last = last->prev;
    } else {
        return;
    }

    ps->len -= last->data.len;
    xfree(last);
}

static inline __attribute__((always_inline))
char strGetChar(const char *s, const size_t len, const long i) {
    return (i >= 0 && i < len) ? s[i] : '\0';
}

char *simplifyPath(char *path) {
    char ch, *res, *tmpch;
    long i, base;
    size_t path_len = strlen(path), n_len;
    Node *n, *tmp = NULL;
    PathStack ps = { 0 };

    stk_push(&ps, node_new(path, 1));
    for (i = 1; (ch = strGetChar(path, path_len, i)) && ch == '/'; i++);

    for (base = i; ; i++) {
        ch = strGetChar(path, path_len, i);

        if (ch == '/' || ch == '\0') {
            n = node_new(path+base, i-base);
            if (!n)
                break;
            tmpch = (char*)n->data.ptr;
            n_len = n->data.len;

            if (!strncmp(tmpch, ".", n_len))
                xfree(n);
            else if (!strncmp(tmpch, "..", n_len))
                stk_pop(&ps);
            else if (!strncmp(tmpch, "...", n_len))
                stk_push(&ps, n);
            else {
                stk_push(&ps, n);
            }

            for ( ; (ch = strGetChar(path, path_len, i)) && ch == '/'; i++);
            if (ch == '\0')
                break;

            base = i;
        }
    }

    res = (char*) calloc(ps.len*2, sizeof(char));
    if (!res)
        return NULL;

    n = ps.first;
    tmpch = res;
    while (n) {
        n_len = n->data.len;
        memmove(res, n->data.ptr, n_len);
        res += n_len;

        if (n->prev && n->next) {
            *res = '/';
            res++;
        }

        tmp = n;
        n = n->next;
        xfree(tmp);
    }

    return tmpch;
}



///////////////////////////////////
/// Test
///////////////////////////////////

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-string>\n", argv[0]);
        return 1;
    }

    char *s = argv[1];
    char *simplified = simplifyPath(s);

    puts(simplified);
    xfree(simplified);
    return 0;
}
