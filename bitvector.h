#ifndef BITVECTOR_H

#include <stdlib.h>
#include <stdint.h>   //for uint32_t meaning fixed size regardless of platform making it portable
#include <stdio.h>
#include <stdbool.h>

// structure for the bit vector
    // array of 32 bit chunks
    // size_t for indicating sizes of objects (unsigned)

typedef struct bitVector{
    uint32_t *memory;
    size_t size; 
}bitVector;


// all functions used
void handle_out_of_memory();
void handle_out_of_bounds(size_t bitPosition, bitVector* vector);
bitVector* bitVectorNew(size_t numberOfBits);
bool bitVectorCheck(bitVector* vector, size_t bitPosition);
void bitVectorSet(bitVector* vector, size_t bitPosition);
void bitVectorFree(bitVector* vactor);

#define BITVECTOR_H
#endif


