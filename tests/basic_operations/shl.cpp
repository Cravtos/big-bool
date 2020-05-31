#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(shl, size_1_shift_0) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl(&a, a, 0);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_1_shift_1) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl(&a, a, 1);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_1_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_shl(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "100");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_4_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1100");

    BB_shl(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_8_shift_4) {
    BB* a = NULL;
    BB* b = NULL;
    BB_from_str(&a, "11001010");

    BB_shl(&b, a, 4);

    const char* a_str = BB_to_str(b);

    ASSERT_STREQ(a_str, "1100" "10100000");

    free((void*) a_str);
    BB_free(a);
    BB_free(b);
}

TEST(shl, size_8_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_shl(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_12_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_shl(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "11000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_12_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_shl(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100" "10101100" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_12_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_shl(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110010" "10110000" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_shl(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "11001111" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_shl(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110010" "10110011" "11000000" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_shl(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100" "10101100" "11110101" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_shl(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "110010" "10110011" "11010100" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_64_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");

    BB_shl(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" \
                "01011010" "00000000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_61_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011");

    BB_shl(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011000");

    free((void*) a_str);
    BB_free(a);
}

TEST(shl, size_64_shift_11) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");

    BB_shl(&a, a, 11);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010" \
                "00000000" "000");

    free((void*) a_str);
    BB_free(a);
}