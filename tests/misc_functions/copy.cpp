#include "gtest/gtest.h"
#include <cstdlib>

extern "C" {
#include "big_bool/big_bool.h"
}

TEST(copy, size_1_value_1) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "1");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "1");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}

TEST(copy, size_1_value_0) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "0");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "0");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}

TEST(copy, size_8) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "10101010");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "10101010");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}

TEST(copy, size_16) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "10101011" "11101010");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "10101011" "11101010");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}

TEST(copy, size_20) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "1010" "10101010" "10101010");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "1010" "10101010" "10101010");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}

TEST(copy, size_64) {
    BB* from = NULL;
    BB* to = NULL;

    BB_from_str(&from, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");
    ASSERT_EQ(BB_copy(&to, from), BB_OK);

    const char* to_str = BB_to_str(to);
    ASSERT_STREQ(to_str, "11001010" "11001111" "01011100" "10101100" "11110101" "11001010" "11001111" "01011010");


    BB_free(from);
    BB_free(to);
    free((void *) to_str);
}
