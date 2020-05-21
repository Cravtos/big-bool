#include "big_bool.h"

#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    BB_srandom(time(NULL));
    BB* a = NULL;
    BB* b = NULL;
    BB* r = NULL;

    BB_from_str(&a, "10110111101111010011");
    BB_shl(&b, a, 17);

    const char* a_str = BB_to_str(a);
    const char* b_str = BB_to_str(b);
    // const char* r_str = BB_to_str(r);

    puts(a_str);
    puts(b_str);
    // puts(r_str);

    return 0;
}
