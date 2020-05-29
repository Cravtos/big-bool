#include "gtest/gtest.h"
#include <cstdlib>
#include <time.h>

extern "C" {
#include "big_bool/big_bool.h"
}

// xor(a, b) == and[or(not(a), not(b)), or(a, b)]
TEST(xor, random_vectors) {
    size_t tests = 1000;

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
        BB *a_not = NULL;
        BB *b_not = NULL;
        BB *ex_or = NULL;

        ASSERT_EQ(BB_random(&a, size), BB_OK);
        ASSERT_EQ(BB_random(&b, size), BB_OK);

//        // To use RecordProperty specify --gtest-output="xml"
//        const char *first_vec = BB_to_str(a);
//        const char *second_vec = BB_to_str(b);
//        RecordProperty("FirstVector", first_vec);
//        RecordProperty("SecondVector", second_vec);

        ASSERT_EQ(BB_not(&a_not, a), BB_OK);
        ASSERT_EQ(BB_not(&b_not, b), BB_OK);

        ASSERT_EQ(BB_xor(&ex_or, a, b), BB_OK);
        const char *first_result = BB_to_str(ex_or);
        ASSERT_NE(first_result, nullptr);

        ASSERT_EQ(BB_or(&a_not, a_not, b_not), BB_OK);
        ASSERT_EQ(BB_or(&b_not, a, b), BB_OK);
        ASSERT_EQ(BB_and(&a_not, a_not, b_not), BB_OK);
        const char *second_result = BB_to_str(a_not);
        ASSERT_NE(second_result, nullptr);

        ASSERT_STREQ(first_result, second_result);

        BB_free(a);
        BB_free(b);
        BB_free(ex_or);
        BB_free(a_not);
        BB_free(b_not);
        free((void *) first_result);
        free((void *) second_result);
    }
}