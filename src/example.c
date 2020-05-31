#include "../include/big_bool/big_bool.h"

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    BB* vec = NULL;
    BB* shl_fs = NULL;
    BB* shr = NULL;
    BB* or = NULL;

    BB_from_str(&vec, "1100101011001111010111001010110011110101110010101100111101011010");
    const char* str = BB_to_str(vec);
    puts(str);
    free(str);

    size_t shift = 11;
    size_t size = vec->last_byte * 8 + vec->last_bit;

    BB_shl_fs(&shl_fs, vec, shift);
    str = BB_to_str(shl_fs);
    puts(str);
    free(str);

    BB_shr(&shr, vec, size - shift);
    str = BB_to_str(shr);
    puts(str);
    free(str);

    BB_or(&or, shl_fs, shr);
    str = BB_to_str(or);
    puts(str);
    free(str);

    BB_free(vec);
    BB_free(shr);
    BB_free(shl_fs);
    BB_free(or);

    return 0;
}