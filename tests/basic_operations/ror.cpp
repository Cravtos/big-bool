#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(ror, size_1_shift_0) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_ror(&a, a, 0);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_1_shift_1) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_ror(&a, a, 1);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_1_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_ror(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_4_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1100");

    BB_ror(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0011");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_8_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_ror(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10101100");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_8_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_ror(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_12_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_ror(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110011001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_12_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_ror(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "101011001100");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_12_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_ror(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "001010110011");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_ror(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100111111001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_ror(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0010101100111111");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_ror(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11110101110010101100");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_ror(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "00111101011100101011");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_64_shift_16) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011010");

    BB_ror(&a, a, 16);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100111101011010110010101100111101011100101011001111010111001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_64_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011010");

    BB_ror(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0101100101011001111010111001010110011110101110010101100111101011");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_64_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011010");

    BB_ror(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0101101011001010110011110101110010101100111101011100101011001111");

    free((void*) a_str);
    BB_free(a);
}

TEST(ror, size_64_shift_11) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011010");

    BB_ror(&a, a, 11);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1110101101011001010110011110101110010101100111101011100101011001");

    free((void*) a_str);
    BB_free(a);
}