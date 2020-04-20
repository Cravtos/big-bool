#include "big_bool.h"

#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    BB_srandom(time(NULL));
    BB* bb1 = BB_random(16);
    BB* bb2 = BB_random(16);
    const char* str_bb1 = BB_to_str(bb1);
    const char* str_bb2 = BB_to_str(bb2);
    printf("\tRandom BB's: \n\t%s\n\t%s\n\t---\n", str_bb1, str_bb2);

    BB* bb_xor = BB_xor(bb1, bb2);
    BB* bb_and = BB_and(bb1, bb2);
    BB* bb_or = BB_or(bb1, bb2);
    BB* bb_not = BB_not(bb1);
    BB* bb_shl = BB_shl(bb1, 3);
    BB* bb_shr = BB_shr(bb1, 4);
    BB* bb_rol = BB_rol(bb1, 5);
    BB* bb_ror = BB_ror(bb1, 7);
    BB* from_number = BB_from_uint64(5817984712);

    // Memory leak here. Not how should be used
    printf("AND\t%s\n", BB_to_str(bb_and));
    printf("OR\t%s\n", BB_to_str(bb_or));
    printf("XOR\t%s\n", BB_to_str(bb_xor));
    printf("NOT\t%s\n", BB_to_str(bb_not));
    printf("SHL3\t%s\n", BB_to_str(bb_shl));
    printf("SHR4\t%s\n", BB_to_str(bb_shr));
    printf("ROL5\t%s\n", BB_to_str(bb_rol));
    printf("ROR7\t%s\n", BB_to_str(bb_ror));
    printf("From Number\t%s\n", BB_to_str(from_number));
    return 0;
}
