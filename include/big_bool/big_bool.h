#ifndef BIG_BOOL_H
#define BIG_BOOL_H

#include <stdint.h>
#include <stdlib.h>


#define BB_NULL_ARG 1
#define BB_CANT_ALLOCATE 2
#define BB_EMPTY_VECTOR 3
#define BB_BAD_STRING 4
#define BB_COPY_ITSELF 5
#define BB_OK 0

struct _BB {
    uint8_t* vector;    // First byte in vector is the least significant byte.
    size_t last_byte;   // length of vector / 8
    size_t last_bit;    // length of vector % 8
};

typedef struct _BB BB;

// Q: Why use double pointer?
// A: To change @r in the callee scope.

// Functions returning int return OK (1) on success and FAIL (0) on fail.

// Constructors
int BB_from_str(BB** r, const char *str);
int BB_from_uint64(BB** r, uint64_t number);
int BB_zero(BB** r, size_t size);
void BB_srandom(size_t seed);            // Set random seed
int BB_random(BB** r, size_t size);      // Generate random BigBool

// Destructor
void BB_free(BB* a);

// Misc
int BB_copy(BB** to, BB* from);
int BB_trim(BB** r);
int BB_resize(BB** r, size_t new_size);

// To string
char* BB_to_str(BB* a);

// Operations
int BB_shr(BB** r, BB* a, size_t n);
int BB_shl(BB** r, BB* a, size_t n);
int BB_shl_fs(BB** r, BB* a, size_t n);  // Vector stays the same size, head cuts
int BB_ror(BB** r, BB* a, size_t n);
int BB_rol(BB** r, BB* a, size_t n);
int BB_and(BB** r, BB* a, BB* b);
int BB_xor(BB** r, BB* a, BB* b);
int BB_or(BB** r, BB* a, BB* b);
int BB_not(BB** r, BB* a);

#endif //BIG_BOOL_H
