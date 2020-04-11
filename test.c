#include "big_bool.h"

#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    BigBool_srandom(time(NULL));
    BigBool* bb1 = BigBool_random(16);
    BigBool* bb2 = BigBool_random(16);
    const char* str_bb1 = BigBool_to_str(bb1);
    const char* str_bb2 = BigBool_to_str(bb2);
    printf("\tRandom BB's: \n\t%s\n\t%s\n\t---\n", str_bb1, str_bb2);

    BigBool* bb_xor = BigBool_xor(bb1, bb2);
    BigBool* bb_and = BigBool_and(bb1, bb2);
    BigBool* bb_or = BigBool_or(bb1, bb2);
    BigBool* bb_not = BigBool_not(bb1);
    BigBool* bb_shl = BigBool_shl(bb1, 3);
    BigBool* bb_shr = BigBool_shr(bb2, 3);

    printf("AND\t%s\n", BigBool_to_str(bb_and));
    printf("OR\t%s\n", BigBool_to_str(bb_or));
    printf("XOR\t%s\n", BigBool_to_str(bb_xor));
    printf("NOTBB1\t%s\n", BigBool_to_str(bb_not));
    printf("SHL3BB1\t%s\n", BigBool_to_str(bb_shl));
    printf("SHR3BB2\t%s\n", BigBool_to_str(bb_shr));
    return 0;
}
