#include "big_bool.h"

#include <string.h>
#include <stdlib.h>

BB* BB_from_uint64(uint64_t number)
{
    size_t last_bit = 0;
    size_t last_byte = 8;

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
    {
        return NULL;
    }
    bb->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }
    bb->last_byte = last_byte;
    bb->last_bit = last_bit;


    for (size_t byte = 0; byte < last_byte; byte++)
    {
        bb->vector[byte] |= number; // % 256
        number >>= 8u;
    }

    return bb;
}

void BB_srandom(size_t seed)
{
    srand(seed);
}

BB* BB_random(size_t size)
{
    size_t last_bit = size % 8;
    size_t last_byte = size / 8;

    if (last_byte == 0 && last_bit == 0)
    {
        return NULL;
    }

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
    {
        return NULL;
    }
    bb->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }
    bb->last_byte = last_byte;
    bb->last_bit = last_bit;

    for (size_t i = 0; i <= last_byte; i++)
    {
        bb->vector[i] = (uint8_t) rand();
    }

    return bb;
}

char* BB_to_str(BB *bb)
{
    size_t last_byte = bb->last_byte;
    size_t last_bit = bb->last_bit;
    size_t len = last_byte * 8 + last_bit;

    char *str = calloc(len + 1, sizeof(char));
    if (str == NULL)
        return NULL;

    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            str[len - (byte * 8 + bit + 1)] = ((bb->vector[byte] >> bit) & 1) + '0';
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        str[len - (last_byte * 8 + bit + 1)] = ((bb->vector[last_byte] >> bit) & 1) + '0';
    }

    return str;
}

BB* str_to_BB(const char *str)
{
    size_t len = strlen(str);
    size_t last_bit = len % 8;
    size_t last_byte = len / 8;

    if (last_byte == 0 && last_bit == 0)
    {
        return NULL;
    }

    for (size_t i = 0; i < len; i++)
        if (str[i] != '0' && str[i] != '1')
            return NULL;

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
    {
        return NULL;
    }
    bb->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }
    bb->last_byte = last_byte;
    bb->last_bit = last_bit;


    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            bb->vector[byte] |= (str[len - (byte * 8 + bit + 1)] - '0') << bit;
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        bb->vector[last_byte] |= (str[len - (last_byte * 8 + bit + 1)] - '0') << bit;
    }

    return bb;
}

void BB_free(BB* bb)
{
    free(bb->vector);
    free(bb);
}

BB* BB_not(BB* bb)
{
    BB* nbb = calloc(1, sizeof(BB));
    if (nbb == NULL)
        return NULL;
    nbb->vector = calloc(bb->last_byte + (bb->last_bit > 0), sizeof(uint8_t));
    if (nbb->vector == NULL)
    {
        free(nbb);
        return NULL;
    }
    nbb->last_byte = bb->last_byte;
    nbb->last_bit = bb->last_bit;

    for (size_t byte = 0; byte <= bb->last_byte; byte++)
    {
        nbb->vector[byte] = ~bb->vector[byte];
    }

    return nbb;
}


BB* BB_and(BB* f, BB* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BB_and(s, f);

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
        return NULL;
    bb->vector = calloc(f->last_byte + (f->last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }

    bb->last_byte = f->last_byte;
    bb->last_bit = f->last_bit;

    for (size_t byte = 0; byte <= s->last_byte; byte++)
    {
        bb->vector[byte] = f->vector[byte] & s->vector[byte];
    }

    return bb;
}

BB* BB_or(BB* f, BB* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BB_or(s, f);

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
        return NULL;
    bb->vector = calloc(f->last_byte + (f->last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }
    bb->last_byte = f->last_byte;
    bb->last_bit = f->last_bit;

    for (size_t byte = 0; byte <= s->last_byte; byte++)
    {
        bb->vector[byte] = f->vector[byte] | s->vector[byte];
    }

    for (size_t byte = s->last_byte + 1; byte <= f->last_byte; byte++)
    {
        bb->vector[byte] = f->vector[byte];
    }

    return bb;
}

BB* BB_xor(BB* f, BB* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BB_xor(s, f);

    BB* bb = calloc(1, sizeof(BB));
    if (bb == NULL)
        return NULL;
    bb->vector = calloc(f->last_byte + (f->last_bit > 0), sizeof(uint8_t));
    if (bb->vector == NULL)
    {
        free(bb);
        return NULL;
    }
    bb->last_byte = f->last_byte;
    bb->last_bit = f->last_bit;

    for (size_t byte = 0; byte <= s->last_byte; byte++)
    {
        bb->vector[byte] = f->vector[byte] ^ s->vector[byte];
    }
    for (size_t byte = s->last_byte + 1; byte <= f->last_byte; byte++)
    {
        bb->vector[byte] = f->vector[byte] ^ (uint8_t) 0;
    }

    return bb;
}

BB* BB_shl(BB* bb, size_t shift)
{
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    BB* sbb = calloc(1, sizeof(BB));
    if (sbb == NULL)
        return NULL;

    sbb->vector = calloc(bb->last_byte * 8 + (bb->last_bit > 0), sizeof(uint8_t));
    if (sbb->vector == NULL)
    {
        free(sbb);
        return NULL;
    }

    sbb->last_byte = bb->last_byte;
    sbb->last_bit = bb->last_bit;

    // Return empty vector (shift is bigger than vector size)
    if (shift >= bb->last_byte * 8 + bb->last_bit)
    {
        return sbb;
    }

    // Shift bits and bytes
    uint8_t to_next_byte = 0;
    for (size_t byte = byte_shift; byte < sbb->last_byte + (sbb->last_bit > 0); byte++)
    {
        uint8_t tmp_to_next_byte = bb->vector[byte - byte_shift] >> (8 - bit_shift);
        sbb->vector[byte] = (bb->vector[byte - byte_shift] << bit_shift) | to_next_byte;
        to_next_byte = tmp_to_next_byte;
    }

    return sbb;
}

BB* BB_shr(BB* bb, size_t shift)
{
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    BB* sbb = calloc(1, sizeof(BB));
    
    if (sbb == NULL)
    {
        return NULL;
    }

    sbb->vector = calloc(bb->last_byte * 8 + (bb->last_bit > 0), sizeof(uint8_t));
    if (sbb->vector == NULL)
    {
        free(sbb);
        return NULL;
    }

    sbb->last_byte = bb->last_byte;
    sbb->last_bit = bb->last_bit;

    // Return empty vector (shift is bigger than vector size)
    if (shift >= bb->last_byte * 8 + bb->last_bit)
    {
        return sbb;
    }

    // Shift bits and bytes
    uint8_t to_next_byte = 0;
    size_t last_not_empty_byte = sbb->last_byte + (sbb->last_bit > 0) - byte_shift - 1;
    for (size_t byte = last_not_empty_byte + 1; byte > 0; byte--)
    {
        uint8_t tmp_to_next_byte = bb->vector[byte - 1 + byte_shift] << (8 - bit_shift);
        sbb->vector[byte - 1] = (bb->vector[byte - 1 + byte_shift] >> bit_shift) | to_next_byte;
        to_next_byte = tmp_to_next_byte;
    }

    return sbb;
}

BB* BB_ror(BB* bb, size_t shift)
{
    size_t size = bb->last_byte * 8 + bb->last_bit;
    shift %= size;
    BB* op1 = BB_shr(bb, shift);
    BB* op2 = BB_shl(bb, size - shift);
    BB* ror = BB_or(op1, op2);
    BB_free(op1);
    BB_free(op2);
    return ror;
}

BB* BB_rol(BB* bb, size_t shift)
{
    size_t size = bb->last_byte * 8 + bb->last_bit;
    shift %= size;
    BB* op1 = BB_shl(bb, shift);
    BB* op2 = BB_shr(bb, size - shift);
    BB* rol = BB_or(op1, op2);
    BB_free(op1);
    BB_free(op2);
    return rol;
}