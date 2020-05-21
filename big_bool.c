#include "big_bool.h"

#include <string.h>
#include <stdlib.h>


// TODO: Trim leading zeros.
// Create vector from number
int BB_from_uint64(BB** r, uint64_t number)
{
    int status = OK;

    if (r == NULL)
    {
        return FAIL;
    }

    if ((*r) != NULL)
    {
        BB_free((*r));
    }

    status = BB_zero(r, sizeof(uint64_t) * 8);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    for (size_t byte = 0; byte < (*r)->last_byte; byte++)
    {
        (*r)->vector[byte] |= number; // % 256
        number >>= 8u;
    }

    return status;
}

// Specifies seed for random.
void BB_srandom(size_t seed)
{
    srand(seed);
}

// Creates random vector.
int BB_random(BB** r, size_t size)
{
    int status = OK;

    if (r==NULL) {
        return FAIL;
    }

    if ((*r)!=NULL) {
        BB_free(*r);
    }

    status = BB_zero(r, size);

    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    for (size_t i = 0; i <= (*r)->last_byte; i++)
    {
        (*r)->vector[i] = (uint8_t) rand();
    }

    return status;
}

// Creates vector filled with zeros.
int BB_zero(BB** r, size_t size)
{
    if (r == NULL)
    {
        return FAIL;
    }

    if ((*r) != NULL)
    {
        BB_free(*r);
    }

    if (size == 0)
    {
        (*r) = NULL;
        return OK;
    }

    size_t last_byte = size / 8;
    size_t last_bit = size % 8;

    (*r) = calloc(1, sizeof(BB));
    if ((*r) == NULL)
        return FAIL;

    (*r)->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));

    if ((*r)->vector == NULL)
    {
        BB_free((*r));
        return FAIL;
    }

    (*r)->last_byte = last_byte;
    (*r)->last_bit = last_bit;

    return OK;
}

// Converts vector to string.
char* BB_to_str(BB *a)
{
    size_t last_byte = a->last_byte;
    size_t last_bit = a->last_bit;
    size_t size = last_byte * 8 + last_bit;

    char *str = calloc(size + 1, sizeof(char));
    if (str == NULL)
        return NULL;

    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            str[size - (byte * 8 + bit + 1)] = ((a->vector[byte] >> bit) & 1) + '0';
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        str[size - (last_byte * 8 + bit + 1)] = ((a->vector[last_byte] >> bit) & 1) + '0';
    }

    return str;
}

// Creates vector from string.
int BB_from_str(BB** r, const char *str)
{
    int status = OK;

    if (r == NULL)
    {
        return FAIL;
    }

    if ((*r) != NULL)
    {
        BB_free(*r);
    }

    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
        if (str[i] != '0' && str[i] != '1')
            return FAIL;

    status = BB_zero(r, len);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    size_t last_byte = (*r)->last_byte;
    size_t last_bit = (*r)->last_bit;

    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            (*r)->vector[byte] |= (str[len - (byte * 8 + bit + 1)] - (unsigned) '0') << bit;
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        (*r)->vector[last_byte] |= (str[len - (last_byte * 8 + bit + 1)] - (unsigned) '0') << bit;
    }

    return OK;
}

// Creates a full copy of vector.
int BB_copy(BB** to, BB* from)
{
    int status = OK;

    if (to == NULL)
        return FAIL;

    if ((*to) == from)
        (*to) = NULL;

    if ((*to) != NULL)
        BB_free((*to));

    (*to) = calloc(1, sizeof(BB));

    if ((*to) == NULL)
        return FAIL;

    status = BB_zero(to, from->last_byte * 8 + from->last_bit);
    if (status == FAIL)
    {
        (*to) = NULL;
        return FAIL;
    }

    memcpy((*to)->vector, from->vector, from->last_byte + (from->last_bit > 0));

    return OK;
}

// Frees vector from memory.
void BB_free(BB* a)
{
    free(a->vector);
    free(a);
}

/*
 * Check if (r == a), (r == NULL) or (r != a) and:
 * If (r == a) -- leave @r unchanged
 * Else -- free @r and point it to new BB of the same size
 * Return FAIL if new BB failed to allocate.
 */
int handle_args(BB** r, BB* a)
{
    int status = OK;
    if (*r != a)
    {
        if (*r != NULL)
            BB_free(*r);

        size_t size = a->last_byte * 8 + a->last_bit;
        status = BB_zero(r, size);
    }
    return status;
}

// Operation NOT (~)
int BB_not(BB** r, BB* a)
{
    if (handle_args(r, a) == FAIL)
        return FAIL;

    for (size_t byte = 0; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = ~a->vector[byte];
    }

    return OK;
}


// Operation AND (&)
int BB_and(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if ((a->last_byte * 8 + a->last_bit) < (b->last_byte * 8 + b->last_bit))
        return BB_and(r, b, a);

    if (handle_args(r, a) == FAIL)
        return FAIL;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] & b->vector[byte];
    }

    return OK;
}

// Operation OR (|)
int BB_or(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if ((a->last_byte * 8 + a->last_bit) < (b->last_byte * 8 + b->last_bit))
        return BB_or(r, b, a);

    if (handle_args(r, a) == FAIL)
        return FAIL;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] | b->vector[byte];
    }

    for (size_t byte = b->last_byte + 1; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return OK;
}

// Operation XOR (^)
int BB_xor(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if ((a->last_byte * 8 + a->last_bit) < (b->last_byte * 8 + b->last_bit))
        return BB_xor(r, b, a);

    if (handle_args(r, a) == FAIL)
        return FAIL;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] ^ b->vector[byte];
    }
    for (size_t byte = b->last_byte + 1; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return OK;
}

// Shift left operation (<<). (Makes vector bigger)
int BB_shl(BB** r, BB* a, size_t shift)
{
    int status = OK;

    if (r == NULL)
        return FAIL;

    int need_to_free = 0;
    if ((*r) == a)
    {
        status = BB_copy(&a, a);
        if (status == FAIL)
        {
            (*r) = NULL;
            return FAIL;
        }
        need_to_free = 1;
    }

    if ((*r) != NULL)
        BB_free(*r);

    size_t a_size = a->last_byte * 8 + a->last_bit;
    status = BB_zero(r, shift + a_size);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;
    uint8_t to_next_byte = 0;

    for (size_t byte = byte_shift; byte < (*r)->last_byte + ((*r)->last_bit > 0); byte++)
    {
        uint8_t tmp_to_next_byte = a->vector[byte - byte_shift] >> (8 - bit_shift);
        (*r)->vector[byte] = a->vector[byte - byte_shift];
        (*r)->vector[byte] <<= bit_shift;
        (*r)->vector[byte] |= to_next_byte;
        to_next_byte = tmp_to_next_byte;
    }

    if (need_to_free == 1)
        BB_free(a);

    return OK;
}

// Shift left operation (<<). (Vector stays the same size, head cuts)
int BB_shl_fs(BB** r, BB* a, size_t shift)
{
    int status = OK;

    if (r == NULL)
        return FAIL;

    int need_to_free = 0;
    if ((*r) == a)
    {
        status = BB_copy(&a, a);
        if (status == FAIL)
        {
            (*r) = NULL;
            return FAIL;
        }
        need_to_free = 1;
    }

    if ((*r) != NULL)
        BB_free(*r);

    size_t a_size = a->last_byte * 8 + a->last_bit;

    if (a_size < shift)
    {
        return BB_zero(r, 1);
    }

    status = BB_zero(r, a_size);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;
    uint8_t to_next_byte = 0;

    for (size_t byte = byte_shift; byte < (*r)->last_byte + ((*r)->last_bit > 0); byte++)
    {
        uint8_t tmp_to_next_byte = a->vector[byte - byte_shift] >> (8 - bit_shift);
        (*r)->vector[byte] = a->vector[byte - byte_shift];
        (*r)->vector[byte] <<= bit_shift;
        (*r)->vector[byte] |= to_next_byte;
        to_next_byte = tmp_to_next_byte;
    }

    if (need_to_free == 1)
        BB_free(a);

    return OK;
}

// Shift right operation (>>). (Makes vector smaller)
int BB_shr(BB** r, BB* a, size_t shift)
{
    int status = OK;

    if (r == NULL)
        return FAIL;

    int need_to_free = 0;
    if ((*r) == a)
    {
        status = BB_copy(&a, a);
        if (status == FAIL)
        {
            (*r) = NULL;
            return FAIL;
        }
        need_to_free = 1;
    }

    if ((*r) != NULL)
        BB_free(*r);

    // Return empty vector (shift is bigger than vector size)
    size_t a_size = a->last_byte * 8 + a->last_bit;
    if (shift >= a_size)
    {
        return BB_zero(r, 1); // return FAIL or OK
    }

    status = BB_zero(r, a_size - shift);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    uint8_t to_next_byte = 0;
    size_t last_not_empty_byte = a->last_byte - byte_shift;

    for (size_t byte = last_not_empty_byte + (1); byte > 0; byte--) // +1 Added to byte to avoid endless loop
    {
        uint8_t tmp_to_next_byte = a->vector[byte - (1)] << (8 - bit_shift);
        (*r)->vector[byte - (1)] = a->vector[byte + byte_shift - (1)];
        (*r)->vector[byte - (1)] >>= bit_shift;
        (*r)->vector[byte - (1)] |= to_next_byte;
        to_next_byte = tmp_to_next_byte;
    }

    if (need_to_free == 1)
        BB_free(a);

    return OK;
}

int BB_ror(BB** r, BB* a, size_t shift)
{
    int status = OK;

    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shr = NULL;
    status = BB_shr(&shr, a, shift);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    BB* shl_fs = NULL;

    status = BB_shl_fs(&shl_fs, a, size - shift);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    status = BB_or(r, shl_fs, shr);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    BB_free(shr);
    BB_free(shl_fs);
    return status;
}

int BB_rol(BB** r, BB* a, size_t shift)
{
    int status = OK;

    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shl_fs = NULL;
    status = BB_shl_fs(&shl_fs, a, shift);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    BB* shr = NULL;
    status = BB_shr(&shr, a, size - shift);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    status = BB_or(r, shl_fs, shr);
    if (status == FAIL)
    {
        (*r) = NULL;
        return FAIL;
    }

    BB_free(shr);
    BB_free(shl_fs);
    return OK;
}