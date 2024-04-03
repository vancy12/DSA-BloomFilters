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

bloomFilter* bloomFilterNew(size_t numFunctions, size_t size, ...);
void bloomFilterFree(bloomFilter* filter);
void bloomFilterSet(bloomFilter* filter, const void* data, size_t length);
void bloomFilterSetString(bloomFilter* filter, const char* str);
bool bloomFilterCheck(bloomFilter* filter, const void* data, size_t length);
bool bloomFilterCheckString(bloomFilter* filter, const char* str);
bloomFilter *bloomFilterNewDefault(size_t size);

#endif