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

    ASSERT_STREQ(a_str, "0");

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
    BB_from_str(&a, "1100" "10101100");

    BB_shl_fs(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001111" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_shl_fs(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11000000" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100" "11110101" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_shl_fs(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11" "11010100" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_64_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011100");

    BB_shl_fs(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011100" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl_fs, size_64_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011100");

    BB_shl_fs(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010110" "01111010" "11100101" "01100111" "10101110" "01010110" "01111010" "11100000");

    free((void*) a_str);
    BB_free(a);
}