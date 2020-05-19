# Big boolean vector library
___

## Implemented functions:
```c
    BB* BB_from_str(const char *str);
    BB* BB_from_uint64(uint64_t number);      
    char* BB_to_str(BB* a);

    BB* BB_zero(size_t n);
    void BB_free(BB* a);                  
    
    void BB_srandom(size_t seed);      
    BB* BB_random(size_t n);           
    
    void BB_shr(BB* r, BB* a, size_t n);
    void BB_shl(BB* r, BB* a, size_t n);
    void BB_ror(BB* r, BB* a, size_t n);
    void BB_rol(BB* r, BB* a, size_t n);
    void BB_and(BB* r, BB* a, BB* b);
    void BB_xor(BB* r, BB* a, BB* b);
    void BB_or(BB* r, BB* a, BB* b);
    void BB_not(BB* r, BB* a);
```

### TODO:
* Trim leading zeros in BB in order to save memory
