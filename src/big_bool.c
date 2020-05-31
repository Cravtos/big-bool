#include "../include/big_bool/big_bool.h"

#include <string.h>
#include <stdlib.h>

#define RETURN_ON_FAIL() if (status != BB_OK) return status

size_t BB_size_in_bits(BB* r)
{
    return r->last_byte * 8 + r->last_bit;
}

int BB_resize(BB** r, size_t new_size_in_bits)
{
    if (r == NULL || (*r) == NULL)
        return BB_NULL_ARG;

    if (new_size_in_bits == 0)
        return BB_EMPTY_VECTOR;

    if (BB_size_in_bits(*r) == new_size_in_bits)
        return BB_OK;

    size_t new_last_byte = new_size_in_bits / 8;
    size_t new_last_bit = new_size_in_bits % 8;

    size_t allocated_bytes = (*r)->last_byte + ((*r)->last_bit > 0);
    size_t new_allocated_bytes = new_last_byte + (new_last_bit > 0);

    (*r)->last_byte = new_size_in_bits / 8;
    (*r)->last_bit = new_size_in_bits % 8;

    if (allocated_bytes == new_allocated_bytes)
    {
        return BB_OK;
    }

    (*r)->vector = realloc((*r)->vector, new_allocated_bytes);
    if ((*r)->vector == NULL)
        return BB_CANT_ALLOCATE;

    return BB_OK;
}

// Create vector from number
int BB_from_uint64(BB** r, uint64_t number)
{
    int status = BB_OK;

    if (r == NULL)
    {
        return BB_NULL_ARG;
    }

    if ((*r) == NULL)
    {
        status = BB_zero(r, sizeof(uint64_t) * 8);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*r) < sizeof(uint64_t) * 8)
    {
        status = BB_resize(r, sizeof(uint64_t) * 8);
        RETURN_ON_FAIL();
    }
    else
    {
        (*r)->last_byte = sizeof(uint64_t);
        (*r)->last_bit = 0;
    }

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0) - 1;
    for (size_t byte = 0; byte <= last_accessible_byte; byte++)
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
int BB_random(BB** r, size_t size_in_bits)
{
    int status = BB_OK;

    if (r == NULL)
        return BB_NULL_ARG;

    if (size_in_bits == 0)
        return BB_EMPTY_VECTOR;

    if ((*r) == NULL)
    {
        status = BB_zero(r, size_in_bits);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*r) < size_in_bits)
    {
        status = BB_resize(r, size_in_bits);
        RETURN_ON_FAIL();
    }
    else
    {
        (*r)->last_byte = size_in_bits / 8;
        (*r)->last_bit = size_in_bits % 8;
    }

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0) - 1;
    for (size_t byte = 0; byte <= last_accessible_byte; byte++)
    {
        (*r)->vector[byte] = (uint8_t) rand();
    }

    return status;
}

// Creates vector filled with zeros.
int BB_zero(BB** r, size_t size_in_bits)
{
    int status = BB_OK;

    if (r == NULL)
        return BB_NULL_ARG;

    if (size_in_bits == 0)
        return BB_EMPTY_VECTOR;

    size_t last_byte = size_in_bits / 8;
    size_t last_bit = size_in_bits % 8;

    if ((*r) == NULL)
    {
        (*r) = calloc(1, sizeof(BB));
        if ((*r) == NULL)
        {
            return BB_CANT_ALLOCATE;
        }

        (*r)->vector = calloc(last_byte + (last_bit > 0), sizeof(uint8_t));
        if ((*r)->vector == NULL)
        {
            BB_free(*r);
            return BB_CANT_ALLOCATE;
        }
    }
    else if (BB_size_in_bits(*r) < size_in_bits)
    {
        status = BB_resize(r, size_in_bits);
        RETURN_ON_FAIL();

        for (size_t byte = 0; byte < last_byte + (last_bit > 0); byte++)
        {
            (*r)->vector[byte] = 0;
        }
    }

    (*r)->last_byte = size_in_bits / 8;
    (*r)->last_bit = size_in_bits % 8;

    return status;
}

// Converts vector to string.
char* BB_to_str(BB *a)
{
    if (a == NULL)
    {
        return NULL;
    }

    size_t significant_bit = a->last_bit;
    size_t significant_byte = a->last_byte;

    // Check if last_byte is accessible (can be used as index)
    if (a->last_bit == 0 && significant_byte > 0)
    {
        significant_byte--;
        significant_bit = 8;
    }
    else /* Null bits beyond scope. */
    {
        a->vector[significant_byte] <<= (8 - significant_bit);
        a->vector[significant_byte] >>= (8 - significant_bit);
    }

    // Get last significant byte and bit
    while (a->vector[significant_byte] == 0 && significant_byte > 0)
    {
        significant_byte--;
        significant_bit = 8;
    }
    while (significant_bit > 0 && ((a->vector[significant_byte] >> (significant_bit - 1)) & 1) == 0)
    {
        significant_bit--;
    }

    // To print 0
    if (significant_bit == 0 && significant_byte == 0)
        significant_bit = 1;

    // Since last_bit is size % 8:
    if (significant_bit == 8)
    {
        significant_byte++;
        significant_bit = 0;
    }

    size_t size = significant_byte * 8 + significant_bit;
    char *str = calloc(size + 1, sizeof(char));
    if (str == NULL)
        return NULL;

    for (size_t byte = 0; byte < significant_byte; byte++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            size_t current_bit = byte * 8 + bit;
            size_t bit_value = (a->vector[byte] >> bit) & 1;
            size_t idx = (size - 1) - current_bit;
            str[idx] = bit_value + '0';
        }
    }

    for (size_t bit = 0; bit < significant_bit; bit++)
    {
        size_t current_bit = significant_byte * 8 + bit;
        size_t bit_value = (a->vector[significant_byte] >> bit) & 1;
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

    size_t last_byte = len / 8;
    size_t last_bit = len % 8;

    if ((*r) == NULL)
    {
        status = BB_zero(r, len);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*r) < len)
    {
        status = BB_resize(r, len);
        RETURN_ON_FAIL();
    }

    (*r)->last_byte = last_byte;
    (*r)->last_bit = last_bit;

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

    return status;
}

// Creates a full copy of vector.
int BB_copy(BB** to, BB* from)
{
    int status = BB_OK;
    if (to == NULL || from == NULL)
        return BB_NULL_ARG;

    if ((*to) == from) /* @to and @from is the same pointer */
        return BB_COPY_ITSELF;

    size_t size = BB_size_in_bits(from);

    if ((*to) == NULL)
    {
        status = BB_zero(to, size);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*to) < size)
    {
        status = BB_resize(to, size);
        RETURN_ON_FAIL();
    }

    (*to)->last_byte = size / 8;
    (*to)->last_bit = size % 8;

    size_t allocated_bytes = from->last_byte + (from->last_bit > 0);
    memcpy((*to)->vector, from->vector, allocated_bytes);

    return status;
}

// Frees vector from memory.
void BB_free(BB* a)
{
    if (a == NULL || a->vector == NULL)
        return;

    free(a->vector);
    free(a);
}

// Removes leading zeros from vector.
int BB_shrink(BB** r)
{
    int status = BB_OK;
    if (r == NULL || (*r) == NULL)
        return BB_NULL_ARG;

    size_t significant_bit = (*r)->last_bit;
    size_t significant_byte = (*r)->last_byte;

    // Check if last_byte is accessible (can be used as index)
    if ((*r)->last_bit == 0 && significant_byte > 0)
    {
        significant_byte--;
        significant_bit = 8;
    }
    else /* Null bits beyond scope. */
    {
        (*r)->vector[significant_byte] <<= (8 - significant_bit);
        (*r)->vector[significant_byte] >>= (8 - significant_bit);
    }

    // Get last significant byte and bit
    while ((*r)->vector[significant_byte] == 0 && significant_byte > 0)
    {
        significant_byte--;
        significant_bit = 8;
    }
    while (significant_bit > 0 && (((*r)->vector[significant_byte] >> (significant_bit - 1)) & 1) == 0)
    {
        significant_bit--;
    }

    // To print 0
    if (significant_bit == 0 && significant_byte == 0)
        significant_bit = 1;

    // Since last_bit is size % 8:
    if (significant_bit == 8)
    {
        significant_byte++;
        significant_bit = 0;
    }

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


/*
 * Compare @r and @a and:
 * If (r == a)    -- leave @r unchanged
 * If (r == NULL) -- create new vector length of @a
 * If (r != NULL) -- resize @r to length of @a with reallocation if needed
 */
int handle_args(BB** r, BB* a)
{
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    int status = BB_OK;

    size_t size = BB_size_in_bits(a);

    if ((*r) != a)
    {
        if ((*r) == NULL)
        {
            status = BB_zero(r, size);
            RETURN_ON_FAIL();
        }
        else if (BB_size_in_bits(*r) < size)
        {
            status = BB_resize(r, size);
            RETURN_ON_FAIL();
        }

        (*r)->last_byte = size / 8;
        (*r)->last_bit = size % 8;
    }

    return status;
}

// Operation NOT (~)
int BB_not(BB** r, BB* a)
{
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    int status = BB_OK;
    status = handle_args(r, a);
    RETURN_ON_FAIL();

    size_t last_accessible_byte = a->last_byte + (a->last_bit > 0) - 1;
    for (size_t byte = 0; byte <= last_accessible_byte; byte++)
    {
        (*r)->vector[byte] = ~a->vector[byte];
    }

    // Null bits beyond size.
    size_t tmp_last_bit = (a->last_bit == 0) ? 8 : a->last_bit;
    (*r)->vector[last_accessible_byte] <<= (8 - tmp_last_bit);
    (*r)->vector[last_accessible_byte] >>= (8 - tmp_last_bit);

    return status;
}


// Operation AND (&)
int BB_and(BB** r, BB* a, BB* b)
{
    if (r == NULL || a == NULL || b == NULL)
        return BB_NULL_ARG;

    // Make first BigBool >= than second
    if (BB_size_in_bits(a) < BB_size_in_bits(b))
        return BB_and(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    RETURN_ON_FAIL();

    size_t last_accessible_byte_b = b->last_byte + (b->last_bit > 0) - 1;
    size_t last_accessible_byte_a = a->last_byte + (a->last_bit > 0) - 1;

    // Null bits beyond size.
    size_t tmp_last_bit = (b->last_bit == 0) ? 8 : b->last_bit;
    b->vector[last_accessible_byte_b] <<= (8 - tmp_last_bit);
    b->vector[last_accessible_byte_b] >>= (8 - tmp_last_bit);

    for (size_t byte = 0; byte <= last_accessible_byte_b; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] & b->vector[byte];
    }

    for (size_t byte = last_accessible_byte_b + 1; byte <= last_accessible_byte_a; byte++)
    {
        (*r)->vector[byte] = 0;
    }

    return status;
}

// Operation OR (|)
int BB_or(BB** r, BB* a, BB* b)
{
    if (r == NULL || a == NULL || b == NULL)
        return BB_NULL_ARG;

    // Make first BigBool >= than second
    if (BB_size_in_bits(a) < BB_size_in_bits(b))
        return BB_or(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    RETURN_ON_FAIL();

    size_t last_accessible_byte_b = b->last_byte + (b->last_bit > 0) - 1;
    size_t last_accessible_byte_a = a->last_byte + (a->last_bit > 0) - 1;

    // Null bits beyond size.
    size_t tmp_last_bit = (b->last_bit == 0) ? 8 : b->last_bit;
    b->vector[last_accessible_byte_b] <<= (8 - tmp_last_bit);
    b->vector[last_accessible_byte_b] >>= (8 - tmp_last_bit);

    for (size_t byte = 0; byte <= last_accessible_byte_b; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] | b->vector[byte];
    }

    for (size_t byte = last_accessible_byte_b + 1; byte <= last_accessible_byte_a; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return status;
}

// Operation XOR (^)
int BB_xor(BB** r, BB* a, BB* b)
{
    if (r == NULL || a == NULL || b == NULL)
        return BB_NULL_ARG;

    // Make first BigBool >= than second
    if (BB_size_in_bits(a) < BB_size_in_bits(b))
        return BB_xor(r, b, a);

    int status = BB_OK;
    status = handle_args(r, a);
    RETURN_ON_FAIL();

    size_t last_accessible_byte_b = b->last_byte + (b->last_bit > 0) - 1;
    size_t last_accessible_byte_a = a->last_byte + (a->last_bit > 0) - 1;

    // Null bits beyond size.
    size_t tmp_last_bit = (b->last_bit == 0) ? 8 : b->last_bit;
    b->vector[last_accessible_byte_b] <<= (8 - tmp_last_bit);
    b->vector[last_accessible_byte_b] >>= (8 - tmp_last_bit);

    for (size_t byte = 0; byte <= last_accessible_byte_b; byte++)
    {
        (*r)->vector[byte] = a->vector[byte] ^ b->vector[byte];
    }

    for (size_t byte = last_accessible_byte_b + 1; byte <= last_accessible_byte_a; byte++)
    {
        (*r)->vector[byte] = a->vector[byte];
    }

    return status;
}

// Shift left operation (<<). (Makes vector bigger)
int BB_shl(BB** r, BB* a, size_t shift)
{
    int status = BB_OK;
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    size_t new_size = BB_size_in_bits(a) + shift;
    if (*r == NULL)
    {
        status = BB_zero(r, new_size);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*r) < new_size)
    {
        status = BB_resize(r, new_size);
        RETURN_ON_FAIL();
    }

    (*r)->last_byte = new_size / 8;
    (*r)->last_bit = new_size % 8;

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0) - 1;

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

    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    // Return empty vector (shift is bigger than vector size)
    if (shift >= BB_size_in_bits(a))
    {
        if ((*r) != NULL)
        {
            (*r)->last_byte = 0;
            (*r)->last_bit = 1;
            (*r)->vector[0] = 0;
            return status;
        }
        else
        {
            status = BB_zero(r, 1);
            return status;
        }
    }

    status = handle_args(r, a);
    RETURN_ON_FAIL();

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_accessible_byte = (*r)->last_byte + ((*r)->last_bit > 0) - 1;

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
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    // Return empty vector (shift is bigger than vector size)
    if (shift >= BB_size_in_bits(a))
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

    size_t last_accessible_byte = a->last_byte + (a->last_bit > 0) - 1;
    size_t new_size = BB_size_in_bits(a) - shift;

    if ((*r) == NULL)
    {
        status = BB_zero(r, BB_size_in_bits(a) - shift);
        RETURN_ON_FAIL();
    }
    else if (BB_size_in_bits(*r) < new_size)
    {
        status = BB_resize(r, BB_size_in_bits(a) - shift);
        RETURN_ON_FAIL();
    }

    (*r)->last_byte = new_size / 8;
    (*r)->last_bit = new_size % 8;

    // Shift bits and bytes
    size_t byte_shift = shift / 8;
    size_t bit_shift = shift % 8;

    size_t last_not_empty_byte = last_accessible_byte - byte_shift;

    for (size_t byte = 0; byte < last_not_empty_byte; byte++)
    {
        uint8_t to_current_byte = a->vector[byte + byte_shift + 1] << (8-bit_shift);
        (*r)->vector[byte] = a->vector[byte + byte_shift];
        (*r)->vector[byte] >>= bit_shift;
        (*r)->vector[byte] |= to_current_byte;
    }

    // Last byte doesn't need any parts of next bytes (obviously), so it's outside the loop.
    if (last_not_empty_byte <= (*r)->last_byte + ((*r)->last_bit > 0) - 1)
    {
        (*r)->vector[last_not_empty_byte] = a->vector[last_not_empty_byte + byte_shift];
        (*r)->vector[last_not_empty_byte] >>= bit_shift;
    }

    return status;
}

// Cycle right-shift operation.
int BB_ror(BB** r, BB* a, size_t shift)
{
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    int status = BB_OK;
    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shr = NULL;
    status = BB_shr(&shr, a, shift);
    RETURN_ON_FAIL();

    BB* shl_fs = NULL;
    status = BB_shl_fs(&shl_fs, a, size - shift);
    if (status != BB_OK)
        goto clean_up_shr;

    status = BB_or(r, shl_fs, shr);
    if (status != BB_OK)
        goto clean_up_shl_fs;

clean_up_shl_fs:
    BB_free(shl_fs);
clean_up_shr:
    BB_free(shr);
    return status;
}

// Cycle left-shift operation.
int BB_rol(BB** r, BB* a, size_t shift)
{
    if (r == NULL || a == NULL)
        return BB_NULL_ARG;

    int status = BB_OK;
    size_t size = a->last_byte * 8 + a->last_bit;
    shift %= size;

    BB* shl_fs = NULL;
    status = BB_shl_fs(&shl_fs, a, shift);
    RETURN_ON_FAIL();

    BB* shr = NULL;
    status = BB_shr(&shr, a, size - shift);
    if (status != BB_OK)
        goto clean_up_shl_fs;

    status = BB_or(r, shl_fs, shr);
    if (status != BB_OK)
        goto clean_up_shr;

clean_up_shr:
    BB_free(shr);
clean_up_shl_fs:
    BB_free(shl_fs);
    return status;
}