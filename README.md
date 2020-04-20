#Big boolean vector library
___

##Implemented functions:
```c
    BB* BB_from_str(const char *);
    BB* BB_from_uint64(uint64_t);
    char* BB_to_str(BB *);
    void BB_free(BB*);

    BB* BB_srandom(size_t);
    BB* BB_random(size_t);
    
    BB* BB_and(BB*, BB*);
    BB* BB_xor(BB*, BB*);
    BB* BB_or(BB*, BB*);
    BB* BB_shr(BB*, size_t);
    BB* BB_shl(BB*, size_t);
    BB* BB_ror(BB*, size_t);
    BB* BB_rol(BB*, size_t);
    BB* BB_not(BB*);
```

###TODO:
1) <s>Convenient function names</s>
2) Trim leading zeros in BB in order to save memory
3) Solve the problem with the ease of memory leakage. <br> 
**(thoughts: change functions to put result in first argument <br> 
OR pass third argument for return)**