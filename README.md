# Big boolean vector library
___

## Implemented functions:
```c
    BigBool* str_to_BigBool(const char *);
    BigBool* uint64_to_BigBool(uint64_t);
    char* BigBool_to_str(BigBool *);
    void BigBool_free(BigBool*);

    BigBool* BigBool_srandom(size_t);
    BigBool* BigBool_random(size_t);
    
    BigBool* BigBool_and(BigBool*, BigBool*);
    BigBool* BigBool_xor(BigBool*, BigBool*);
    BigBool* BigBool_or(BigBool*, BigBool*);
    BigBool* BigBool_shr(BigBool*, size_t);
    BigBool* BigBool_shl(BigBool*, size_t);
    BigBool* BigBool_ror(BigBool*, size_t);
    BigBool* BigBool_rol(BigBool*, size_t);
    BigBool* BigBool_not(BigBool*);
```

### TODO:
1) Convenient function names
2) Trim leading zeros in BB in order to save memory
3) Solve the problem with the ease of memory leakage. <br> 
**(thoughts: change functions to put result in first argument <br> 
OR pass third argument for return)**
