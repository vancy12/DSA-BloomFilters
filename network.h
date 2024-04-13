#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "bloomfilter.h"

#define N 8 // Assuming the graph has 8 nodes

typedef struct node{
    int num;
    bloomFilter* filter;
    struct node* next;
}node;

typedef struct Graph {
    int numVertices;
    struct node** adjLists;
    int* visited;
}Graph;

#endif