#ifndef __LL_H
#define __LL_H

# include <stdlib.h>
# include <sys/types.h>

struct __node {
    int64_t value;
    struct __node *next;
};

typedef struct __node Node;

#endif
