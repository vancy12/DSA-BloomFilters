#include <stdio.h>
#include <stdlib.h>

#include "bloomfilter.h"

int main(){
    bloomFilter *filter = bloomFilterNewDefault(1024);
    bloomFilterSetString(filter, "abc");
    printf("%d\n", bloomFilterCheckString(filter, "abc"));
    printf("%d\n", bloomFilterCheckString(filter, "bcd"));
    printf("%d\n", bloomFilterCheckString(filter, "0"));
    printf("%d\n", bloomFilterCheckString(filter, "1"));
    bloomFilterSetString(filter, "2");
    printf("%d\n", bloomFilterCheckString(filter, "2"));
    return 0;
}