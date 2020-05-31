#ifndef BIG_BOOL_H
#define BIG_BOOL_H

#include <stdint.h>
#include <stdlib.h>

/* ------------------------------------------
 *   # Error codes
 * ------------------------------------------
 */
#define BB_NULL_ARG 1
#define BB_CANT_ALLOCATE 2
#define BB_EMPTY_VECTOR 3
#define BB_BAD_STRING 4
#define BB_COPY_ITSELF 5
#define BB_OK 0
// ------------------------------------------

/* ------------------------------------------
 * # Main structure
 * ------------------------------------------
 * It has uint8_t pointer to hold vector data (LSB)
 * and two size_t variables for indexing:
 *      last_byte == vector length / 8
 *       last_bit == vector length % 8
 */
struct _BB {
    uint8_t* vector;
    size_t last_byte;
    size_t last_bit;
};
typedef struct _BB BB;
// ------------------------------------------

// Result argument (@r) is double pointer because it can change @r in the callee scope.
/* - Arguments for result:
 * 1) Can take pointer to NULL and point it to new vector (therefore it must to be cleaned),
 * 2) Can take pointer to already existing vector and:
 *    2.1) Resize it, if its size is less than needed for holding result
 *    2.2) Change size variables, if its size is more than needed.
 */

/* ------------------------------------------
 *  # Constructors
 * ------------------------------------------
 */

/*  int BB_from_str(BB** r, const char *str);
 *
 *  - Description:
 *  Takes string containing only '1' and '0' and makes vector of it.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_EMPTY_VECTOR if strlen(str) == 0,
 *  BB_BAD_STRING if string is not only '1' or '0',
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero).
 */
int BB_from_str(BB** r, const char *str);

/*  int BB_from_uint64(BB** r, uint64_t number);
 *
 *  - Description:
 *  Takes 64 bit number and makes vector of it.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero).
 */
int BB_from_uint64(BB** r, uint64_t number);

/*  int BB_zero(BB** r, size_t size);
 *
 *  - Description:
 *  Creates vector of specified size and full of zeros.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_EMPTY_VECTOR if size == 0,
 *  BB_CANT_ALLOCATE if memory fails to allocate,
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_zero(BB** r, size_t size);

/*  int BB_random(BB** r, size_t size);
 *
 *  - Description:
 *  Creates random vector of specified size. Seed is set by BB_srandom.
 *  Uses C rand() function. Has limited randomness.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_EMPTY_VECTOR if size == 0,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_random(BB** r, size_t size);

/*  int BB_copy(BB** to, BB* from);
 *
 *  - Description:
 *  Makes result vector a copy of other vector.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_COPY_ITSELF if ((*to) == from),
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_copy(BB** to, BB* from);
/* ------------------------------------------ */

/* ------------------------------------------
 *   # Destructors
 * ------------------------------------------
 */

/*  void BB_free(BB* a);
 *
 *  - Description:
 *  Free's memory allocated for vector.
 *  It is a good practice to NULL pointer after using BB_free.
 *
 *  - Return value:
 *  None.
 *
 *  - Known bugs:
 *  Crash on double free.
 */
void BB_free(BB* a);
// ------------------------------------------

/* ------------------------------------------
 *   # Misc functions
 * ------------------------------------------
 */

/*  void BB_srandom(size_t seed);
 *
 *  - Description:
 *  Sets seed for generating random vectors.
 *  Uses C srand() function.
 *
 *  - Return value:
 *  None.
 */
void BB_srandom(size_t seed);

/*  int BB_shrink(BB** r);
 *
 *  - Description:
 *  Cuts all leading zeros, reallocates memory for vector, so it takes less memory.
 *  Also changes size variables of vector.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL
 *  BB_CANT_ALLOCATE if fails to reallocate memory for vector.
 */
int BB_shrink(BB** r);

/*  char* BB_to_str(BB* a);
 *
 *  - Description:
 *  Allocates and returns string representing vector values. (should be cleaned)
 *  Leading zeros are cutted.
 *  If vector size of 0 is given (though it can't be created using constructors),
 *  then it returns string length of 0.
 *
 *  - Return value:
 *  Pointer to string
 *  NULL, if failed to allocate.
 */
char* BB_to_str(BB* a);

/*  int BB_resize(BB** r, size_t new_size);
 *
 *  - Description:
 *  Reallocates memory for vector given new size.
 *  Changes size variables of vector.
 *  Old memory is copied, new memory is undefined.
 *
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_CANT_ALLOCATE if failed to allocate memory for vector,
 *  BB_EMPTY_VECTOR if new_size == 0.
 */
int BB_resize(BB** r, size_t new_size);
// ------------------------------------------


/* ------------------------------------------
 *   # Mathematical operations
 * ------------------------------------------
 *
 * See begining of header file for explanations on result pointer.
 *
 */

/*  int BB_shr(BB** r, BB* a, size_t n);
 *
 *  - Description:
 *  Shifts vector right on n positions. Vector becomes smaller.
 *  If shift is bigger than vector size, zero vector size of 1 is returned.
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_CANT_ALLOCATE [only if *r == NULL] if fails to allocate memory for vector.
 */
int BB_shr(BB** r, BB* a, size_t n);

/*  int BB_shl(BB** r, BB* a, size_t n);
 *
 *  - Description:
 *  Shifts vector left on n positions. Vector becomes bigger.
 *  If shift is bigger than vector size, zero vector size of 1 is returned.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_shl(BB** r, BB* a, size_t n);

/*  int BB_shl_fs(BB** r, BB* a, size_t n);
 *
 *  - Description:
 *  Shifts vector left on n positions. Vector stays the same size.
 *  If shift is bigger than vector size, zero vector size of 1 is returned.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_shl_fs(BB** r, BB* a, size_t n);

/*  int BB_ror(BB** r, BB* a, size_t n);
 *
 *  - Description:
 *  Makes cyclic shift right on n positions.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_ror(BB** r, BB* a, size_t n);

/*  int BB_rol(BB** r, BB* a, size_t n);
 *
 *  - Description:
 *  Makes cyclic shift left on n positions.
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_rol(BB** r, BB* a, size_t n);

/*  int BB_and(BB** r, BB* a, BB* b);
 *
 *  - Description:
 *  Makes "logical and" operaion on vectors pointed by (a) and (b).
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_and(BB** r, BB* a, BB* b);

/*  int BB_xor(BB** r, BB* a, BB* b);
 *
 *  - Description:
 *  Makes "logical xor" operaion on vectors pointed by (a) and (b).
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_xor(BB** r, BB* a, BB* b);

/*  int BB_or(BB** r, BB* a, BB* b);
 *
 *  - Description:
 *  Makes "logical or" operaion on vectors pointed by (a) and (b).
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_or(BB** r, BB* a, BB* b);

/*  int BB_not(BB** r, BB* a);
 *
 *  - Description:
 *  Makes "logical not" operaion on vector pointed by (a).
 *
 *  - Return value:
 *  BB_OK on success,
 *  BB_NULL_ARG if r == NULL,
 *  BB_zero error codes, [only if *r == NULL] (see BB_zero),
 *  BB_resize error codes, [only if (*r != NULL && (length of vector *r) < size)] (See BB_resize).
 */
int BB_not(BB** r, BB* a);
// ------------------------------------------

#endif //BIG_BOOL_H
