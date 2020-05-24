#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

// FAIL == 1
// OK == 0

// can't use define from big_bool because of conflicts with gtest

TEST(BB_zero, size_0) {
    BB* a = NULL;
    ASSERT_EQ(BB_zero(&a, 0), BB_FAIL);
    ASSERT_EQ(a, nullptr);
}

TEST(BB_from_str, empty_string) {
    BB* a = NULL;
    ASSERT_EQ(BB_from_str(&a, ""), BB_FAIL);
    ASSERT_EQ(a, nullptr);
}

TEST(BB_random, size_0) {
    BB* a = NULL;
    ASSERT_EQ(BB_random(&a, 0), BB_FAIL);
    ASSERT_EQ(a, nullptr);
}

TEST(BB_from_uint64, 0) {
    BB* a = NULL;
    ASSERT_EQ(BB_from_uint64(&a, 0), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "0000000000000000000000000000000000000000000000000000000000000000");

    BB_free(a);
    free((void *) a_str);
}

TEST(BB_from_uint64, minus_1) {
    BB* a = NULL;
    ASSERT_EQ(BB_from_uint64(&a, -1), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "1111111111111111111111111111111111111111111111111111111111111111");

    BB_free(a);
    free((void *) a_str);
}

