// NOTE: clangd.inactiveRegions.useBackgroundHighlight in the clangd for VSCode settings might make this easier to read
// https://stackoverflow.com/questions/78735704/how-to-disable-coloring-out-the-section-of-code-between-macros

#if defined(VEC_T) && defined(VEC_NAME)
#include <stdbool.h>
#include <stddef.h>

#define DEFINE_VEC(type)                                                                                               \
    typedef struct {                                                                                                   \
        VEC_T* p;                                                                                                      \
        size_t capacity;                                                                                               \
        size_t len;                                                                                                    \
    } type;

#ifndef DEFN
DEFINE_VEC(VEC_NAME)
#endif

#define CONCAT(x, y) CONCAT_1(x, y)
#define CONCAT_1(x, y) x##y

#define DEFAULT_CAP 16

#ifndef DEFN
#ifdef VEC_IMPL
#include "vector.c"
#else
// [VEC_NAME]_with_capacity: Initializes an empty vector or a vector with the given capacity.
VEC_NAME* CONCAT(VEC_NAME, _with_capacity)(const size_t capacity);

// [VEC_NAME]_new: Initializes an empty vector or a vector with a capacity of 16.
VEC_NAME* CONCAT(VEC_NAME, _new)();

// [VEC_NAME]_resize: Resize the vector.
void CONCAT(VEC_NAME, _resize)(VEC_NAME* vec, const size_t new_capacity);

// [VEC_NAME]_len: Returns the current number of elements in the vector.
size_t CONCAT(VEC_NAME, _len)(VEC_NAME* vec);

// [VEC_NAME]_get: Accesses an element by index.
VEC_T* CONCAT(VEC_NAME, _get)(const VEC_NAME* vec, const size_t i);

// [VEC_NAME]_set: Updates the value at a specific index.
void CONCAT(VEC_NAME, _set)(VEC_NAME* vec, const size_t i, const VEC_T val);

// [VEC_NAME]_push: Adds an element to the end of the vector.
void CONCAT(VEC_NAME, _push)(VEC_NAME* vec, const VEC_T* val);

// [VEC_NAME]_pop: Removes the last element from the vector.
void CONCAT(VEC_NAME, _pop)(VEC_NAME* vec);

// [VEC_NAME]_insert: Inserts an element at the specified index.
void CONCAT(VEC_NAME, _insert)(VEC_NAME* vec, const size_t i, const VEC_T val);

// [VEC_NAME]_erase: Removes an element from the specific index.
void CONCAT(VEC_NAME, _erase)(VEC_NAME* vec, const size_t i);

// [VEC_NAME]_empty: Checks whether the vector is empty.
bool CONCAT(VEC_NAME, _empty)(VEC_NAME* vec);

// [VEC_NAME]_clear: Clears all the elements from the vector.
void CONCAT(VEC_NAME, _clear)(VEC_NAME* vec);

// [VEC_NAME]_free: Frees vector's allocated memory.
void CONCAT(VEC_NAME, _free)(VEC_NAME* vec);
#endif
#endif

#ifdef DEFN
#undef DEFN
#else
#ifdef VEC_T
#undef VEC_T
#endif

#ifdef VEC_NAME
#undef VEC_NAME
#endif

#ifdef VEC_IMPL
#undef VEC_IMPL
#endif
#endif

#endif