#include "big_bool.h"

#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    BB_srandom(time(NULL));
    BB* a = NULL;

    BB_from_str(&a, "10011001");
    const char* a_str = BB_to_str(a);
    puts(a_str);
    free(a_str);

    BB_rol(&a, a, 9);
    a_str = BB_to_str(a);
    puts(a_str);
    free(a_str);

    return 0;
}
