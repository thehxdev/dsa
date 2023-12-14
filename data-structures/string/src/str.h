#ifndef STR_H
#define STR_H


#if !defined (_DEFAULT_SOURCE)          \
    || !defined (__USE_XOPEN_EXTENDED)  \
    || _XOPEN_SOURCE < 500              \
    || _POSIX_C_SOURCE < 200809L
/**
 * Duplicate and return exact same malloc'd string.
 * This string is always null terminated.
 *
 * `strdup` is not a standard C functoin, so if the program
 * compiles with ANSI C compiler (Not GNU) this functoin must
 * be manually written.
 *
 * @s: source string.
 * ---
 * @ret: duplicated malloc'd `s` | NULL
 */
char *strdup(const char *s);
#endif /* strdup */


#ifndef size_t
# define size_t unsigned long
#endif /* size_t */


/*
 * String type definition
 * These strings are always null terminated.
 */
typedef struct __string String;


/* create a new String */
String *str_new(const char *s);

/* free a string from memory */
void str_free(String **sp);

/* get character pointer of String */
char *str_ptr(String *sp);

/* get length of String */
size_t str_len(String *sp);

/* concatinate two strings */
String *str_concat(const char *s1, const char *s2);

/* capitalize a string */
void str_capitalize(String *sp);

#endif /* STR_H */
