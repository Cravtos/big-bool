#include "gtest/gtest.h"
#include <cstdlib>
#include <time.h>

extern "C" {
#include "big_bool/big_bool.h"
}

// Shift forward and backward cyclic
TEST(ror_and_rol, random_vectors) {
    size_t tests = 10000000;

    time_t seed = time(NULL);
    BB_srandom(seed);
    srand(seed);

    for (size_t test = 0; test < tests; test++)
    {
        size_t size = rand() % 128 + 1;
        size_t shift = rand() % 256 + 1;

        BB *a = NULL;
        ASSERT_EQ(BB_random(&a, size), BB_OK);
        char *before = BB_to_str(a);
        ASSERT_NE(before, nullptr);

        ASSERT_EQ(BB_rol(&a, a, shift), BB_OK);
        ASSERT_EQ(BB_ror(&a, a, shift), BB_OK);
        char *after = BB_to_str(a);
        ASSERT_NE(before, nullptr);

        ASSERT_STREQ(before, after);

        BB_free(a);
        free((void *) before);
        free((void *) after);
    }
}

// Shift forward and backward
TEST(shl_and_shr, random_vectors) {
    size_t tests = 10000000;

    time_t seed = time(NULL);
    BB_srandom(seed);
    srand(seed);

    for (size_t test = 0; test < tests; test++)
    {
        size_t size = rand() % 128 + 1;
        size_t shift = rand() % 256 + 1;

        BB *a = NULL;
        ASSERT_EQ(BB_random(&a, size), BB_OK);
        const char *before = BB_to_str(a);
        ASSERT_NE(before, nullptr);

        ASSERT_EQ(BB_shl(&a, a, shift), BB_OK);
        ASSERT_EQ(BB_shr(&a, a, shift), BB_OK);
        const char *after = BB_to_str(a);
        ASSERT_NE(after, nullptr);

        ASSERT_STREQ(before, after);

        BB_free(a);
        free((void *) before);
        free((void *) after);
    }
}