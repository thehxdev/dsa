#ifndef HELPERS_H
#define HELPERS_H

/* check NULL pointer in conditional statements */
#define is_null(p) (!(p))

/* check NULL pointer befor calling `free` */
#define check_then_free(p) if ((p)) free((p))

#endif /* HELPERS_H */
