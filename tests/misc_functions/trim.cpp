#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(trim, size_1_value_0) {
    BB* a = NULL;

    BB_from_str(&a, "0");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "0");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_1_value_1) {
    BB* a = NULL;

    BB_from_str(&a, "1");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "1");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_4) {
    BB* a = NULL;

    BB_from_str(&a, "0010");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "10");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_8) {
    BB* a = NULL;

    BB_from_str(&a, "00001010");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "1010");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_8_value_1) {
    BB* a = NULL;

    BB_from_str(&a, "11111111");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "11111111");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_8_value_0) {
    BB* a = NULL;

    BB_from_str(&a, "00000000");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "0");

    BB_free(a);
    free((void *) a_str);
}


TEST(trim, size_12) {
    BB* a = NULL;

    BB_from_str(&a, "000100001010");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "100001010");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_64_value_0) {
    BB* a = NULL;

    BB_from_str(&a, "0000000000000000000000000000000000000000000000000000000000000000");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "0");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_64_value_1) {
    BB* a = NULL;

    BB_from_str(&a, "1111111111111111111111111111111111111111111111111111111111111111");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "1111111111111111111111111111111111111111111111111111111111111111");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_35_value_1) {
    BB* a = NULL;

    BB_from_str(&a, "11111111111111111111111111111111111");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "11111111111111111111111111111111111");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_35_result_8) {
    BB* a = NULL;

    BB_from_str(&a, "00000000000000000000000000010000000");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "10000000");

    BB_free(a);
    free((void *) a_str);
}

TEST(trim, size_35) {
    BB* a = NULL;

    BB_from_str(&a, "00000000000001000000001000000001000");
    ASSERT_EQ(BB_trim(&a), BB_OK);

    const char* a_str = BB_to_str(a);
    ASSERT_STREQ(a_str, "1000000001000000001000");

    BB_free(a);
    free((void *) a_str);
}