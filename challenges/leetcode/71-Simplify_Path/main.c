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

char *simplifyPath(char *path) {
    char ch;
    Node *n, *tmp = NULL;
    PathStack ps = { 0 };

    stk_push(&ps, node_new(path, 1));
    while ((ch = *path++, ch && ch == '/'));

    int i = 1;
    while (1) {
        ch = *path;

        if (ch == '/' || ch == 0) {
            n = node_new(path-i, i);

            if (!strncmp(n->data.ptr, "../", i+1))
                stk_pop(&ps);
            else if (!strncmp(n->data.ptr, "./", i+1))
                xfree(n);
            else
                stk_push(&ps, n);

            while ((ch = *path++, ch && ch == '/'));
            if (ch == 0)
                break;

            i = 0;
        } else {
            path++;
        }

        i++;
    } // end while

    char *res = (char*) malloc(sizeof(char) * (ps.len+1));
    if (!res)
        return NULL;

    size_t nlen;
    n = ps.first;
    size_t offset = ps.len;
    while (n) {
        nlen = n->data.len;
        memmove(res, n->data.ptr, nlen);
        res += nlen;

        if (n->prev && n->next) {
            *res = '/';
            res++;
            offset++;
        }

        tmp = n;
        n = n->next;
        xfree(tmp);
    }

    return (res-offset);
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
