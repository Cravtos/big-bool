#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(xor, size_4) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "0011");
    BB_from_str(&b, "0101");
    BB_xor(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "0110");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(xor, size_8) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00110011");
    BB_from_str(&b, "01010101");
    BB_xor(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "01100110");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(xor, size_12) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "001100110011");
    BB_from_str(&b, "010101010101");
    BB_xor(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "011001100110");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(xor, size_16) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "0011001100110011");
    BB_from_str(&b, "0101010101010101");
    BB_xor(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "0110011001100110");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(xor, size_20) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00110011001100110011");
    BB_from_str(&b, "01010101010101010101");
    BB_xor(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "01100110011001100110");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(xor, size_64) {
    BB* a = NULL;
    BB* b = NULL;

    BB_from_str(&a, "0011001100110011001100110011001100110011001100110011001100110011");
    BB_from_str(&b, "0101010101010101010101010101010101010101010101010101010101010101");
    BB_xor(&a, a, b);

    const char* a_str = BB_to_str(a);

    ASSERT_STREQ(a_str, "0110011001100110011001100110011001100110011001100110011001100110");

    free((void*) a_str);
    BB_free(a);
    BB_free(b);
}

TEST(xor, size_64_itself) {
    BB* a = NULL;

    BB_from_str(&a, "0011001100110011001100110011001100110011001100110011001100110011");
    BB_xor(&a, a, a);
    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "0000000000000000000000000000000000000000000000000000000000000000");

    free((void*) a_str);
    BB_free(a);
}