# Big boolean vector library
___

## Implemented functions:
```c
    // Constructors
    int BB_from_uint64(BB** r, uint64_t number);
    int BB_from_str(BB** r, const char *str);
    int BB_random(BB** r, size_t size);   
    int BB_zero(BB** r, size_t size);
    void BB_srandom(size_t seed);           
    
    // Destructor
    void BB_free(BB* a);
    
    // Misc
    int BB_copy(BB** to, BB* from);
    int BB_shrink(BB** r);
    
    // To string
    char* BB_to_str(BB* a);
    
    // Operations
    int BB_shl_fs(BB** r, BB* a, size_t n);  
    int BB_shr(BB** r, BB* a, size_t n);
    int BB_shl(BB** r, BB* a, size_t n);
    int BB_ror(BB** r, BB* a, size_t n);
    int BB_rol(BB** r, BB* a, size_t n);
    int BB_and(BB** r, BB* a, BB* b);
    int BB_xor(BB** r, BB* a, BB* b);
    int BB_or(BB** r, BB* a, BB* b);
    int BB_not(BB** r, BB* a);
```
