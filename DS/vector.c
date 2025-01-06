// NOTE: clangd.inactiveRegions.useBackgroundHighlight in the clangd for VSCode settings might make this easier to read
// https://stackoverflow.com/questions/78735704/how-to-disable-coloring-out-the-section-of-code-between-macros

#if defined(VEC_T) && defined(VEC_NAME)

#include <stdbool.h>
#include <stdlib.h>
#define DEFN
#include "vector.h"

VEC_NAME* CONCAT(VEC_NAME, _with_capacity)(const size_t capacity)
{
    VEC_NAME* vec = malloc(sizeof(VEC_NAME));
    vec->p        = malloc(sizeof(VEC_T) * capacity);
    vec->capacity = capacity;

    return vec;
}

extern inline VEC_NAME* CONCAT(VEC_NAME, _new)() { return CONCAT(VEC_NAME, _with_capacity)(DEFAULT_CAP); }

void CONCAT(VEC_NAME, _resize)(VEC_NAME* vec, const size_t new_capacity)
{
    vec->p        = realloc(vec->p, new_capacity * sizeof (VEC_T));
    vec->capacity = new_capacity;
}

extern inline size_t CONCAT(VEC_NAME, _len)(VEC_NAME* vec) { return vec->len; };

extern inline VEC_T* CONCAT(VEC_NAME, _get)(const VEC_NAME* vec, const size_t i)
{
    return vec->p + i;
}

extern inline void CONCAT(VEC_NAME, _set)(VEC_NAME* vec, const size_t i, const VEC_T val) { *(vec->p + i) = val; }

void CONCAT(VEC_NAME, _push)(VEC_NAME* vec, const VEC_T val)
{
    if (vec->capacity == vec->len) {
        CONCAT(VEC_NAME, _resize)(vec, vec->capacity * 2);
    }
    *(vec->p + vec->len) = val;

    vec->len++;
}

extern inline void CONCAT(VEC_NAME, _pop)(VEC_NAME* vec) { vec->len--; }

void CONCAT(VEC_NAME, _insert)(VEC_NAME* vec, const size_t i, const VEC_T val)
{
    if (vec->capacity == vec->len) {
        CONCAT(VEC_NAME, _resize)(vec, vec->capacity * 2);
    }
    VEC_T* p   = CONCAT(VEC_NAME, _get)(vec, i);
    VEC_T* end = vec->p + vec->len;
    while (end > p) {
        *(end - 1) = *end;
        end--;
    }
    vec->len++;
    CONCAT(VEC_NAME, _set)(vec, i, val);
}

void CONCAT(VEC_NAME, _erase)(VEC_NAME* vec, const size_t i)
{
    VEC_T* p   = CONCAT(VEC_NAME, _get)(vec, i);
    VEC_T* end = vec->p + vec->len;
    while (p < end) {
        *(p + 1) = *p;
    }
    vec->len--;
}

extern inline bool CONCAT(VEC_NAME, _empty)(VEC_NAME* vec) { return vec->len == 0; }

extern inline void CONCAT(VEC_NAME, _clear)(VEC_NAME* vec) { vec->len = 0; }

void CONCAT(VEC_NAME, _free)(VEC_NAME* vec)
{
    free(vec->p);
    free(vec);
}
#endif