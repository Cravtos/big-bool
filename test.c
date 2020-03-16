#include "big_bool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
        return 0;
    BigBool* f = str_to_BigBool(argv[1]);
    const char *before = BigBool_to_str(f);

    BigBool* t = BigBool_ror(f, strtoul(argv[2], NULL, 10));
    const char *after = BigBool_to_str(t);

    
    printf("Before:\t %s\n", before);
    printf("After:\t %s\n", after);


    return 0;
}
