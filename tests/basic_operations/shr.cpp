#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(shr, size_1_shift_0) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shr(&a, a, 0);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_1_shift_1) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shr(&a, a, 1);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_1_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shr(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_4_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1100");

    BB_shr(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_8_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_shr(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_8_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_shr(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_12_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shr(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_12_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shr(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_12_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shr(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_shr(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_shr(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_shr(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110010101100");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_shr(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100101011");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_64_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101010101");

    BB_shr(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010110011110101110010101100111101011100101011001111");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_64_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101010101");

    BB_shr(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100101011001111010111001010110011110101110010101100111101010");

    free((void*) a_str);
    BB_free(a);
}

TEST(shr, size_64_shift_11) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101010101");

    BB_shr(&a, a, 11);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010110011110101110010101100111101011100101011001");

    free((void*) a_str);
    BB_free(a);
}