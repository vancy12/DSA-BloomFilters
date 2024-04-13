#include "bloomfilter.h"
#include "murmurhash.c"

#define DJB2_INIT 5381

uint32_t djb2(const void *buff, size_t length) {
    uint32_t hash = DJB2_INIT;
    const uint8_t *data = buff;
    for(size_t i = 0; i < length; i++) {
         hash = ((hash << 5) + hash) + data[i]; 
    }
    // printf("djb2:%" PRIu32 "\n", hash);
    return hash;
}
uint32_t sdbm(const void *buff, size_t length) {
    uint32_t hash = 0;
    const uint8_t *data = buff;
    for(size_t i = 0; i < length; i++) {
        hash = data[i] + (hash << 6) + (hash << 16) - hash;
    }
    // printf("sdbm:%" PRIu32 "\n", hash);
    return hash;
}

