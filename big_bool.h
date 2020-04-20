#ifndef BIG_BOOL_H
#define BIG_BOOL_H

#include <stdint.h>
#include <stdlib.h>

struct _BB {
    uint8_t* vector;
    size_t last_byte;   // Last accessible byte in vector
    size_t last_bit;    // Amount of bits
};

typedef struct _BB BB;

BB* BB_from_uint64(uint64_t);   // Make BigBool from uint64 (e.g. 7 -> '111')
BB* BB_from_str(const char *);
char* BB_to_str(BB *);
void BB_free(BB*);            // Delete BigBool from memory

void BB_srandom(size_t seed);  // Set random seed
BB* BB_random(size_t);    // Generate random BigBool

BB* BB_and(BB*, BB*);
BB* BB_xor(BB*, BB*);
BB* BB_or(BB*, BB*);
BB* BB_shr(BB*, size_t);
BB* BB_shl(BB*, size_t);
BB* BB_ror(BB*, size_t);
BB* BB_rol(BB*, size_t);
BB* BB_not(BB*);

#endif //BIG_BOOL_H
