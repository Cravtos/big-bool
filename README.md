#Big boolean vector library
___

##Implemented functions:
```c
    BigBool* str_to_BigBool(const char *);
    BigBool* BigBool_random(size_t);
    char* BigBool_to_str(BigBool *);
    // TODO: BigBool* uint64_to_BigBool(uint64_t);

    void BigBool_free(BigBool*);
    
    BigBool* BigBool_and(BigBool*, BigBool*);
    BigBool* BigBool_or(BigBool*, BigBool*);
    BigBool* BigBool_xor(BigBool*, BigBool*);
    BigBool* BigBool_shr(BigBool*, size_t);
    BigBool* BigBool_shl(BigBool*, size_t);
    BigBool* BigBool_ror(BigBool*, size_t);
    BigBool* BigBool_rol(BigBool*, size_t);
    BigBool* BigBool_not(BigBool*);
```