#include "bitvector.h"
#define BYTE_TO_BITS 8
#define TO_BITS(type) (BYTE_TO_BITS * (sizeof(type)))

//   TO_BITS(uint32_t) ( 8 * 4 ) --> ( 32 ) bits
// allocating space for bitVector

void handle_out_of_memory() {
    fprintf(stderr, "Out of memory.\n");
    exit(EXIT_FAILURE);
}

void handle_out_of_bounds(size_t bitPosition, bitVector* vector){
    fprintf(stderr, "Out of bounds bit_idx=%zu, vect->size=%zu\n", bitPosition, vector->size);
    exit(EXIT_FAILURE);
}


bitVector* bitVectorNew(size_t numberOfBits){
    bitVector* vector = (bitVector*)malloc(sizeof(bitVector));

    if(!vector){
        handle_out_of_memory();
    }

    size_t memorySize = numberOfBits / TO_BITS(uint32_t);

    // checking if it leaves a remainder , if so assign an extra chunk
    if(numberOfBits % TO_BITS(uint32_t) != 0){
        memorySize++;
    }

    // allocate all zeroes by using calloc
    vector->memory = (uint32_t*)calloc(memorySize, sizeof(uint32_t));

    if(!vector->memory){
        handle_out_of_memory();
    }
    vector->size = numberOfBits;
    return vector;
}


// checking the nth bit in bit vector to see if 1 or 0
bool bitVectorCheck(bitVector* vector, size_t bitPosition){
    if(bitPosition >= vector->size){
        handle_out_of_bounds(bitPosition, vector);
    }

    size_t chunkOffset = bitPosition / TO_BITS(uint32_t);

    // equivalent to % operations but less CPU operations
    size_t bitOffset = bitPosition & (TO_BITS(uint32_t) - 1);

    // check that chunk at that bit by right shifting and getting that bit to the LSB
    uint32_t _32bytechunk = vector->memory[chunkOffset];

    return (_32bytechunk >> bitOffset) & 1;
}


// setting the bit to 1
void bitVectorSet(bitVector* vector, size_t bitPosition){
    if(bitPosition >= vector->size){
        handle_out_of_bounds(bitPosition, vector);
    }

    size_t chunkOffset = bitPosition / TO_BITS(uint32_t);
    size_t bitOffset = bitPosition & (TO_BITS(uint32_t) - 1);
    uint32_t *_32bytechunk = &(vector->memory[chunkOffset]);

    // default 1 is an integer which can vary in size on different platform
    // we want unsigned 32 bit makes it portable
    *_32bytechunk |= ((uint32_t)1) << bitOffset;

}




