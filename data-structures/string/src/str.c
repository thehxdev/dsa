#include <stdlib.h>
#include <memory.h>
#include <string.h>


/* str.h */
#include "str.h"
#include "helpers.h"

#define is_capital(ch) ((ch) >= 97 && (ch) <= 122)


#if !defined (_DEFAULT_SOURCE)          \
    || !defined (__USE_XOPEN_EXTENDED)  \
    || _XOPEN_SOURCE < 500              \
    || _POSIX_C_SOURCE < 200809L
char *strdup(const char *s) {
    if (is_null(s))
        return NULL;

    size_t len = strlen(s) + 1;
    char *new = (char*) malloc(sizeof(char) * len);
    if (!new)
        return NULL;

    memmove(new, s, len-1);
    new[len-1] = '\0';
    return new;
}
#endif /* strdup */


typedef struct __string {
    char *__ptr;
    size_t __len;
} String;


String *str_new(const char *s) {
    String *str = (String*) malloc(sizeof(String));
    if (is_null(str))
        return NULL;

    str->__len = (s) ? strlen(s) : 0;
    str->__ptr = (s) ? strdup(s) : NULL;

    return str;
}


void str_free(String **sp) {
    String *s = *sp;
    if (s) {
        check_then_free(s->__ptr);
        free(s);
    }
}


char *str_ptr(String *sp) {
    return (sp) ? sp->__ptr : NULL;
}


size_t str_len(String *sp) {
    return (sp) ? sp->__len : 0;
}


String *str_concat(const char *s1, const char *s2) {
    size_t i;
    String *new = str_new(NULL);

    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);
    new->__len = s1_len + s2_len + 1;

    new->__ptr = malloc(sizeof(char) * new->__len);

    for (i = 0; i < s1_len; i++)
        new->__ptr[i] = s1[i];
    for (i = 0; i < s2_len; i++)
        new->__ptr[i + s1_len] = s2[i];
    new->__ptr[new->__len - 1] = '\0';

    return new;
}


void str_capitalize(String *sp) {
    char *s = str_ptr(sp);

    if (is_capital(s[0]))
        s[0] = s[0] - 32;

    for (size_t i = 1; i < str_len(sp); i++)
        if (s[i - 1] == ' ' && is_capital(s[i]))
            s[i] = s[i] - 32;
}
