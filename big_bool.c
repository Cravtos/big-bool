#include "big_bool.h"

#include <string.h>

char* BigBool_to_str(BigBool *bb)
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

BigBool* str_to_BigBool(const char *str)
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

    BigBool* bb = calloc(1, sizeof(BigBool));
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

void BigBool_free(BigBool* bb)
{
    free(bb->vector);
    free(bb);
}

BigBool* BigBool_not(BigBool* bb)
{
    BigBool* nbb = calloc(1, sizeof(BigBool));
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


BigBool* BigBool_and(BigBool* f, BigBool* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BigBool_and(s, f);

    BigBool* bb = calloc(1, sizeof(BigBool));
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

BigBool* BigBool_or(BigBool* f, BigBool* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BigBool_and(s, f);

    BigBool* bb = calloc(1, sizeof(BigBool));
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

BigBool* BigBool_xor(BigBool* f, BigBool* s)
{
    // Make first BigBool >= than second
    if ((f->last_byte * 8 + f->last_bit) < (s->last_byte * 8 + s->last_bit))
        return BigBool_and(s, f);

    BigBool* bb = calloc(1, sizeof(BigBool));
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

BigBool* BigBool_shl(BigBool* bb, size_t shift)
{
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    BigBool* sbb = calloc(1, sizeof(BigBool));
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

BigBool* BigBool_shr(BigBool* bb, size_t shift)
{
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    BigBool* sbb = calloc(1, sizeof(BigBool));
    
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
