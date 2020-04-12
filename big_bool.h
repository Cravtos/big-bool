#ifndef BIG_BOOL_H
#define BIG_BOOL_H

#include <stdint.h>
#include <stdlib.h>

struct _BigBool {
    uint8_t* vector;
    size_t last_byte;   // Last accessible byte in vector
    size_t last_bit;    // Amount of bits
};

typedef struct _BigBool BigBool;

BigBool* uint64_to_BigBool(uint64_t);   // Make BigBool from uint64 (e.g. 7 -> '111')
BigBool* str_to_BigBool(const char *);
char* BigBool_to_str(BigBool *);
void BigBool_free(BigBool*);            // Delete BigBool from memory

void BigBool_srandom(size_t seed);  // Set random seed
BigBool* BigBool_random(size_t);    // Generate random BigBool

BigBool* BigBool_and(BigBool*, BigBool*);
BigBool* BigBool_xor(BigBool*, BigBool*);
BigBool* BigBool_or(BigBool*, BigBool*);
BigBool* BigBool_shr(BigBool*, size_t);
BigBool* BigBool_shl(BigBool*, size_t);
BigBool* BigBool_ror(BigBool*, size_t);
BigBool* BigBool_rol(BigBool*, size_t);
BigBool* BigBool_not(BigBool*);

#endif //BIG_BOOL_H
