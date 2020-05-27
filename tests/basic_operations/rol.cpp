#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(rol, size_1_shift_0) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_rol(&a, a, 0);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_1_shift_1) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_rol(&a, a, 1);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_1_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1");

    BB_rol(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_4_shift_2) {
    BB* a = NULL;
    BB_from_str(&a, "1100");

    BB_rol(&a, a, 2);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_8_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_rol(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "10101100");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_8_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010");

    BB_rol(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_12_shift_4) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_rol(&a, a, 4);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010" "11001100");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_12_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_rol(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100" "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_12_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100");

    BB_rol(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11" "00101011");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_16_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_rol(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11001111" "11001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_16_shift_14) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111");

    BB_rol(&a, a, 14);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11110010" "10110011");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_20_shift_8) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_rol(&a, a, 8);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1100" "111101011" "1001010");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_20_shift_10) {
    BB* a = NULL;
    BB_from_str(&a, "1100" "10101100" "11110101");

    BB_rol(&a, a, 10);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "11" "11010111" "00101011");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_64_shift_16) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");

    BB_rol(&a, a, 16);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1011100" "10101100" "11110101" "11001010" "11001111" "01011010" "11001010" "11001111");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_64_shift_3) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");

    BB_rol(&a, a, 3);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1010110" "01111010" "11100101" "01100111" "10101110" "01010110" "01111010" "11010110");

    free((void*) a_str);
    BB_free(a);
}

TEST(rol, size_64_shift_11) {
    BB* a = NULL;
    BB_from_str(&a, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");

    BB_rol(&a, a, 11);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "1111010" "11100101" "01100111" "10101110" "01010110" "01111010" "11010110" "01010110");

    free((void*) a_str);
    BB_free(a);
}