#include "bloomfilter.h"
// include hash functions header file

// allocating memory to bloom filter(number of hash functions, how big the bloom filter is, ...)

bloomFilter* bloomFilterNew(size_t numFunctions, size_t size, ...){
    bloomFilter *filter = (bloomFilter*)malloc(sizeof(bloomFilter));

    if(filter == NULL){
        handle_out_of_memory();
    }
    filter->totalBitsSet = 0;
    filter->numberHashFunctions = numFunctions;
    filter->vector = bitVectorNew(size);
    filter->hash_functions = malloc(sizeof(hash32_func) * numFunctions);

    if(filter->hash_functions == NULL){
        handle_out_of_memory();
    }
    va_list argp;
    va_start(argp, numFunctions);
    for (unsigned i = 0; i < numFunctions; i++){
        filter->hash_functions[i] = va_arg(argp, hash32_func);
    }
    va_end(argp);
    return filter;
}

bloomFilter *bloomFilterNewDefault(size_t size) {
    return bloomFilterNew(size, 2, djb2, sdbm);
}

void bloomFilterFree(bloomFilter* filter){
    bitVectorFree(filter->vector);
    free(filter->hash_functions);
    free(filter);
}

void bloomFilterSet(bloomFilter* filter, const void* data, size_t length){

    for(int i = 0; i < filter->numberHashFunctions; i++){
        uint32_t hashValue = filter->hash_functions[i](length, data);
        bitVectorSet(filter->vector, hashValue % filter->vector->size);
    }
    filter->totalBitsSet++;
}

// helper function
void bloomFilterSetString(bloomFilter* filter, const char* str){
    bloomFilterSet(filter, str, strlen(str));
}


// if string is inputted check if the corresponding bits are set

bool bloomFilterCheck(bloomFilter* filter, const void* data, size_t length){
    for(int i = 0; i < filter->numberHashFunctions; i++){
        uint32_t hashValue = filter->hash_functions[i](length, data);
        if(!bitVectorCheck(filter->vector, hashValue % filter->vector->size)){
            return false;
        }
    }

    return true;
}

bool bloomFilterCheckString(bloomFilter* filter, const char* str){
    return bloomFilterCheck(filter, str, strlen(str));
}




