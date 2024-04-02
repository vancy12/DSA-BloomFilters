#ifndef BLOOM_H
#define BLOOM_H

#include "bitvector.h"
#include <stdint.h>
#include <stdbool.h>

// initializing a pointer to the hash functions
// takes the size and void pointer to data as arguments and returns a 32bit hash value

typedef int32_t(*hash32_func)(size_t length, const void* data);


typedef struct bloomFilter{
    bitVector* vector;
    hash32_func *hash_functions;
    size_t numberHashFunctions;
    size_t totalBitsSet;
}bloomFilter;



#endif