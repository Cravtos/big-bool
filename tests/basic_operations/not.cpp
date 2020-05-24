#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(not, size_4) {
    BB* a = NULL;

    BB_from_str(&a, "0101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010");

    free((void*) a_str);
    BB_free(a);
}

TEST(not, size_8) {
    BB* a = NULL;

    BB_from_str(&a, "01010101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10101010");

    free((void*) a_str);
    BB_free(a);
}

TEST(not, size_12) {
    BB* a = NULL;

    BB_from_str(&a, "010101010101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "101010101010");

    free((void*) a_str);
    BB_free(a);
}

TEST(not, size_16) {
    BB* a = NULL;

    BB_from_str(&a, "0101010101010101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010101010101010");

    free((void*) a_str);
    BB_free(a);
}

TEST(not, size_20) {
    BB* a = NULL;

    BB_from_str(&a, "01010101010101010101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10101010101010101010");

    free((void*) a_str);
    BB_free(a);
}

TEST(not, size_64) {
    BB* a = NULL;

    BB_from_str(&a, "0101010101010101010101010101010101010101010101010101010101010101");
    BB_not(&a, a);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010101010101010101010101010101010101010101010101010101010101010");

    free((void*) a_str);
    BB_free(a);
}