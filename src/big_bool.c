#include "../include/big_bool/big_bool.h"

#include <string.h>
#include <stdlib.h>

#define CHECK_ALLOCATION(r) if (status == BB_CANT_ALLOCATE) return BB_CANT_ALLOCATE

size_t size_in_bits(BB* r)
{
    return r->last_byte * 8 + r->last_bit;
}

// Create vector from number
int BB_from_uint64(BB** r, uint64_t number)
{
    int status = BB_OK;

    if (r == NULL)
    {
        return BB_NULL_ARG;
    }

    status = BB_zero(r, sizeof(uint64_t) * 8);
    CHECK_ALLOCATION(*r);

    for (size_t byte = 0; byte <= (*r)->last_byte; byte++)
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
    int status = BB_OK;

    if (r == NULL)
        return BB_NULL_ARG;

    if (size == 0)
        return BB_EMPTY_VECTOR;

    status = BB_zero(r, size);
    CHECK_ALLOCATION(*r);

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
        return BB_NULL_ARG;

    if (size == 0)
        return BB_EMPTY_VECTOR;

    size_t last_byte = size / 8;
    size_t last_bit = size % 8;

    (*r) = calloc(1, sizeof(BB));
    if ((*r) == NULL)
        return BB_CANT_ALLOCATE;

    (*r)->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));
    if ((*r)->vector == NULL)
    {
        BB_free(*r);
        return BB_CANT_ALLOCATE;
    }

    (*r)->last_byte = last_byte;
    (*r)->last_bit = last_bit;
    return BB_OK;
}

// Converts vector to string.
char* BB_to_str(BB *a)
{
    size_t last_byte = a->last_byte;
    size_t last_bit = a->last_bit;
    size_t size = size_in_bits(a);

    char *str = calloc(size + 1, sizeof(char));
    if (str == NULL)
        return NULL;

    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            size_t current_bit = byte * 8 + bit;
            size_t bit_value = (a->vector[byte] >> bit) & 1;
            size_t idx = (size - 1) - current_bit;
            str[idx] = bit_value + '0';
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        size_t current_bit = last_byte * 8 + bit;
        size_t bit_value = (a->vector[last_byte] >> bit) & 1;
        size_t idx = (size - 1) - current_bit;
        str[idx] = bit_value + '0';
    }

    return str;
}

// Creates vector from string.
int BB_from_str(BB** r, const char *str)
{
    int status = BB_OK;

    if (r == NULL)
        return BB_NULL_ARG;

    size_t len = strlen(str);

    if (len == 0)
        return BB_EMPTY_VECTOR;

    for (size_t i = 0; i < len; i++)
        if (str[i] != '0' && str[i] != '1')
            return BB_BAD_STRING;

    status = BB_zero(r, len);
    CHECK_ALLOCATION(*r);

    size_t last_byte = (*r)->last_byte;
    size_t last_bit = (*r)->last_bit;

    for (size_t byte = 0; byte < last_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            size_t current_bit = byte * 8 + bit;
            size_t idx = (len - 1) - current_bit;
            size_t bit_mask = (str[idx] - '0') << bit;
            (*r)->vector[byte] |= bit_mask;
        }
    }

    for (size_t bit = 0; bit < last_bit; bit++)
    {
        size_t current_bit = last_byte * 8 + bit;
        size_t idx = (len - 1) - current_bit;
        size_t bit_mask = (str[idx] - '0') << bit;
        (*r)->vector[last_byte] |= bit_mask;
    }

    return BB_OK;
}

// Creates a full copy of vector.
int BB_copy(BB** to, BB* from)
{
    int status = BB_OK;
    if (to == NULL)
        return BB_NULL_ARG;

    if ((*to) == from) /* @to and @from is the same pointer */
        return BB_COPY_ITSELF;

    status = BB_zero(to, size_in_bits(from));
    CHECK_ALLOCATION(*to);

    size_t allocated_bytes = from->last_byte + (from->last_bit > 0);
    memcpy((*to)->vector, from->vector, allocated_bytes);
    return BB_OK;
}

// Frees vector from memory.
void BB_free(BB* a)
{
    free(a->vector);
    free(a);
}

// Removes leading zeros from vector.
int BB_trim(BB** r)
{
    int status = BB_OK;
    if (r == NULL || (*r) == NULL)
        return BB_NULL_ARG;

    size_t significant_bit = 7;
    size_t significant_byte = (*r)->last_byte;
    if ((*r)->last_bit == 0)
        significant_byte--;

    // Get last significant byte and bit
    while ((*r)->vector[significant_byte] == 0 && significant_byte > 0)
    {
        significant_byte--;
    }
    while ((((*r)->vector[significant_byte] >> significant_bit) & 1) == 0 && significant_bit > 0)
    {
        significant_bit--;
    }
    significant_bit++;

    // Reallocate memory
    size_t allocated_bytes = significant_byte + (significant_bit > 0);
    (*r)->vector = realloc((*r)->vector, allocated_bytes);
    if ((*r) == NULL)
        return BB_CANT_ALLOCATE;

    // Change vector sizes
    (*r)->last_byte = significant_byte;
    (*r)->last_bit = significant_bit;
    return status;
}

int BB_resize(BB** r, size_t new_size)
{
    if (r == NULL || (*r) == NULL)
        return BB_NULL_ARG;

    if (new_size == 0)
        return BB_EMPTY_VECTOR;

    if (size_in_bits(*r) == new_size)
        return BB_OK;

    size_t new_last_byte = new_size / 8;
    size_t new_last_bit = new_size % 8;

    size_t allocated_bytes = (*r)->last_byte + ((*r)->last_bit > 0);
    size_t new_allocated_bytes = new_last_byte + (new_last_bit > 0);

    (*r)->last_byte = new_size / 8;
    (*r)->last_bit = new_size % 8;

    if (allocated_bytes == new_allocated_bytes)
    {
        return BB_OK;
    }

    (*r)->vector = realloc((*r)->vector, new_allocated_bytes);
    if ((*r)->vector == NULL)
        return BB_CANT_ALLOCATE;

    return BB_OK;
}

/*
 * Compare @r and @a and:
 * If (r == a)    -- leave @r unchanged
 * If (r == NULL) -- create new vector length of @a
 * If (r != NULL) -- resize @r to length of @a
 */
int handle_args(BB** r, BB* a)
{
    int status = BB_OK;
    if ((*r) != a)
    {
        if ((*r) != NULL)
        {
            status = BB_resize(r, size_in_bits(a));
            if (status != BB_OK)
                return status;
        }
        else if ((*r) == NULL)
        {
            status = BB_zero(r, size_in_bits(a));
        }
    }
    return status;
}

// Operation NOT (~)
int BB_not(BB** r, BB* a)
{
    int status = BB_OK;
    status = handle_args(r, a);
    if (status != BB_OK)
        return status;

    for (size_t byte = 0; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = ~a->vector[byte];
    }

    return status;
}


// Operation AND (&)
int BB_and(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if (size_in_bits(a) < size_in_bits(b))
        return BB_and(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    if (status != BB_OK)
        return status;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] & b->vector[byte];
    }

    return status;
}

// Operation OR (|)
int BB_or(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if (size_in_bits(a) < size_in_bits(b))
        return BB_or(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    if (status != BB_OK)
        return status;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] | b->vector[byte];
    }

    for (size_t byte = b->last_byte + 1; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return status;
}

// Operation XOR (^)
int BB_xor(BB** r, BB* a, BB* b)
{
    // Make first BigBool >= than second
    if (size_in_bits(a) < size_in_bits(b))
        return BB_xor(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    if (status != BB_OK)
        return status;

    for (size_t byte = 0; byte <= b->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] ^ b->vector[byte];
    }
    for (size_t byte = b->last_byte + 1; byte <= a->last_byte; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return status;
}

// Shift left operation (<<). (Makes vector bigger)
int BB_shl(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;
    if (r == NULL)
        return BB_NULL_ARG;

    if (*r == NULL)
    {
        status = BB_zero(r, shift + size_in_bits(a));
        CHECK_ALLOCATION(*r);
    }
    else
    {
        status = BB_resize(r, shift + size_in_bits(a));
        if (status != BB_OK)
            return status;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0);
    if ((*r)->last_bit == 0)
        last_accessible_byte--;

    for (size_t byte = last_accessible_byte; byte > byte_shift; byte--)
    {
        uint8_t to_current_byte = a->vector[byte - byte_shift - 1] >> (8 - bit_shift);
        (*r)->vector[byte] = a->vector[byte - byte_shift];
        (*r)->vector[byte] <<= bit_shift;
        (*r)->vector[byte] |= to_current_byte;
    }

    // First byte doesn't need any parts of previous bytes (obviously), so it's outside the loop.
    (*r)->vector[byte_shift] = a->vector[0];
    (*r)->vector[byte_shift] <<= bit_shift;

    // Null remaining bits
    for (size_t byte = 0; byte < byte_shift; byte++)
    {
        (*r)->vector[byte] = 0;
    }
    (*r)->vector[byte_shift] >>= bit_shift;
    (*r)->vector[byte_shift] <<= bit_shift;

    return status;
}

// Shift left operation (<<). (Vector stays the same size, head cuts)
int BB_shl_fs(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;

    if (r == NULL)
        return BB_NULL_ARG;

    if ((*r) != a)
    {
        if ((*r) != NULL)
        {
            status = BB_resize(r, size_in_bits(a));
            if (status != BB_OK)
            {
                return status;
            }
        }
        else
        {
            status = BB_zero(r, size_in_bits(a));
            CHECK_ALLOCATION(*r);
        }
    }

    if (size_in_bits(a) <= shift)
    {
        (*r)->last_byte = 0;
        (*r)->last_bit = 1;
        (*r)->vector[0] = 0;
        return BB_OK;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0);
    if ((*r)->last_bit == 0)
        last_accessible_byte--;

    for (size_t byte = last_accessible_byte; byte > byte_shift; byte--)
    {
        uint8_t to_current_byte = a->vector[byte - byte_shift - 1] >> (8 - bit_shift);
        (*r)->vector[byte] = a->vector[byte - byte_shift];
        (*r)->vector[byte] <<= bit_shift;
        (*r)->vector[byte] |= to_current_byte;
    }

    // First byte doesn't need any parts of previous bytes (obviously), so it's outside the loop.
    (*r)->vector[byte_shift] = a->vector[0];
    (*r)->vector[byte_shift] <<= bit_shift;

    // Null remaining bits
    for (size_t byte = 0; byte < byte_shift; byte++)
    {
        (*r)->vector[byte] = 0;
    }
    (*r)->vector[byte_shift] >>= bit_shift;
    (*r)->vector[byte_shift] <<= bit_shift;

    return status;
}

// Shift right operation (>>). (Makes vector smaller)
int BB_shr(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;
    if (r == NULL)
        return BB_NULL_ARG;

    // Return empty vector (shift is bigger than vector size)
    if (shift >= size_in_bits(a))
    {
        if ((*r) != NULL)
        {
            (*r)->last_byte = 0;
            (*r)->last_bit = 1;
            (*r)->vector[0] = 0;
            return BB_OK;
        }
        else
        {
            return BB_zero(r, 1);
        }
    }

    if ((*r) == NULL)
    {
        status = BB_zero(r, size_in_bits(a) - shift);
        if (status != BB_OK)
            return status;
    }
    else if ((*r) != a)
    {
        status = BB_resize(r, size_in_bits(a) - shift);
        if (status != BB_OK)
            return status;
    }

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_accessible_byte = a->last_byte + (a->last_bit > 0) - 1;
    size_t last_not_empty_byte = last_accessible_byte - byte_shift;

    for (size_t byte = 0; byte < last_not_empty_byte; byte++)
    {
        uint8_t to_current_byte = a->vector[byte + byte_shift + 1] << (8-bit_shift);
        (*r)->vector[byte] = a->vector[byte + byte_shift];
        (*r)->vector[byte] >>= bit_shift;
        (*r)->vector[byte] |= to_current_byte;
    }

    // Last byte doesn't need any parts of next bytes (obviously), so it's outside the loop.
    (*r)->vector[last_not_empty_byte] = a->vector[last_not_empty_byte + byte_shift];
    (*r)->vector[last_not_empty_byte] >>= bit_shift;

    if ((*r) == a)
    {
        size_t new_size = size_in_bits(a) - shift;
        (*r)->last_byte = new_size / 8;
        (*r)->last_bit = new_size % 8;
    }

    return status;
}

// Cycle right-shift operation.
int BB_ror(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;
    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shr = NULL;
    status = BB_shr(&shr, a, shift);
    CHECK_ALLOCATION(*r);

    BB* shl_fs = NULL;
    status = BB_shl_fs(&shl_fs, a, size - shift);
    CHECK_ALLOCATION(*r);

    status = BB_or(r, shl_fs, shr);
    CHECK_ALLOCATION(*r);

    BB_free(shr);
    BB_free(shl_fs);
    return status;
}

// Cycle left-shift operation.
int BB_rol(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;
    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shl_fs = NULL;
    status = BB_shl_fs(&shl_fs, a, shift);
    CHECK_ALLOCATION(*r);

    BB* shr = NULL;
    status = BB_shr(&shr, a, size - shift);
    CHECK_ALLOCATION(*r);

    status = BB_or(r, shl_fs, shr);
    CHECK_ALLOCATION(*r);

    BB_free(shr);
    BB_free(shl_fs);
    return status;
}