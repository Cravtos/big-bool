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

char* BigBool_to_str(BigBool *);
BigBool* str_to_BigBool(const char *);
void BigBool_free(BigBool*);
// TODO: BigBool* uint64_to_BigBool(uint64_t);

BigBool* BigBool_random(size_t);
void BigBool_srandom(size_t seed);

BigBool* BigBool_and(BigBool*, BigBool*);
BigBool* BigBool_or(BigBool*, BigBool*);
BigBool* BigBool_xor(BigBool*, BigBool*);
BigBool* BigBool_shr(BigBool*, size_t);
BigBool* BigBool_shl(BigBool*, size_t);
BigBool* BigBool_ror(BigBool*, size_t);
BigBool* BigBool_rol(BigBool*, size_t);
BigBool* BigBool_not(BigBool*);

#endif //BIG_BOOL_H
