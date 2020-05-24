#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(shl_fs, size_1_shift_0) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl_fs(&a, a, 0);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_1_shift_1) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl_fs(&a, a, 1);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_1_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl_fs(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_4_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1100");

    BB_shl_fs(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_8_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_shl_fs(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10100000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_8_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_12_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shl_fs(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "101011000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_12_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110000000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_12_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "110010101100");

    BB_shl_fs(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "000000000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100111100000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111");

    BB_shl_fs(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100000000000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001111010100000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "11001010110011110101");

    BB_shl_fs(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "00111101010000000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_64_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011100");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100111101011100101011001111010111001010110011110101110000000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_64_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "1100101011001111010111001010110011110101110010101100111101011100");

    BB_shl_fs(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0101011001111010111001010110011110101110010101100111101011100000");

    free((void*) a_str);
    BB_free(a);
}