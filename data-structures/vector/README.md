# Vector

A vector (Dynamic array) implementation that works with `int64_t`, `char` and also `char *` or strings.

## Macros

1. `vecTnum`

Used to specify the `vecT` macro. I used 2 macros for vector type because I can compare `vecTnum` with numbers
to specify vector type.

2. `vecT`

Defines the vector's content type.
Supported types:

- `int64_t`
- `char`
- `char *` (string)

