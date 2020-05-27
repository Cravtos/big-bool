#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(or, size_4) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "0011");
    BB_from_str(&b, "0101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_8) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00110011");
    BB_from_str(&b, "01010101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "1110111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_16_3) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00000000" "00000000");
    BB_from_str(&b, "111");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_12) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "0011" "00110011");
    BB_from_str(&b, "0101" "01010101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "111" "01110111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_16) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00110011" "00110011");
    BB_from_str(&b, "01010101" "01010101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "1110111" "01110111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_20) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "0011" "00110011" "00110011");
    BB_from_str(&b, "0101" "01010101" "01010101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "111" "01110111" "01110111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}

TEST(or, size_64) {
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "00110011" "00110011" "00110011" "00110011" "00110011" "00110011" "00110011" "00110011");
    BB_from_str(&b, "01010101" "01010101" "01010101" "01010101" "01010101" "01010101" "01010101" "01010101");
    BB_or(&r, a, b);

    const char* r_str = BB_to_str(r);

    ASSERT_STREQ(r_str, "1110111" "01110111" "01110111" "01110111" "01110111" "01110111" "01110111" "01110111");

    free((void*) r_str);
    BB_free(a);
    BB_free(b);
    BB_free(r);
}