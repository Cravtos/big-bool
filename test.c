#include "big_bool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    BigBool* f = str_to_BigBool(argv[1]);

    BigBool* t = BigBool_shl(f, 3);
    const char *str1 = BigBool_to_str(t);

    puts(str1);

    return 0;
}
