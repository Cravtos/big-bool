#include "gtest/gtest.h"
#include <cstdlib>
#include <time.h>

extern "C" {
#include "big_bool/big_bool.h"
}

// not(and(a, b)) == or(not(a), not(b))
TEST(de_morgan, random_vectors) {
    size_t tests = 1000000;

    time_t seed = time(NULL);
    BB_srandom(seed);
    srand(seed);

    for (size_t test = 0; test < tests; test++)
    {
        /*
         * Vectors should be same size. Otherwise NOT operation will invert only allocated
         * memory, but should invert memory equal of size of the biggest vector
         */
        size_t size = rand() % 128 + 1;

        BB *a = NULL;
        BB *b = NULL;
        BB *a_copy = NULL;
        BB *b_copy = NULL;

        ASSERT_EQ(BB_random(&a, size), BB_OK);
        ASSERT_EQ(BB_random(&b, size), BB_OK);

//        // To use RecordProperty specify --gtest-output="xml"
//        const char *first_vec = BB_to_str(a);
//        const char *second_vec = BB_to_str(b);
//        RecordProperty("FirstVector", first_vec);
//        RecordProperty("SecondVector", second_vec);

        ASSERT_EQ(BB_copy(&a_copy, a), BB_OK);
        ASSERT_EQ(BB_copy(&b_copy, b), BB_OK);

        ASSERT_EQ(BB_and(&a, a, b), BB_OK);
        ASSERT_EQ(BB_not(&a, a), BB_OK);

        const char *first_result = BB_to_str(a);
        ASSERT_NE(first_result, nullptr);

        ASSERT_EQ(BB_not(&a_copy, a_copy), BB_OK);
        ASSERT_EQ(BB_not(&b_copy, b_copy), BB_OK);
        ASSERT_EQ(BB_or(&a_copy, a_copy, b_copy), BB_OK);

        const char *second_result = BB_to_str(a_copy);
        ASSERT_NE(second_result, nullptr);

        ASSERT_STREQ(first_result, second_result);

        BB_free(a);
        BB_free(b);
        BB_free(a_copy);
        BB_free(b_copy);
        free((void *) first_result);
        free((void *) second_result);
//        free((void *) first_vec);
//        free((void *) second_vec);
    }
}