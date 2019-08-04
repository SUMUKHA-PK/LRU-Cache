#include<stdio.h>
#include<stdlib.h>

typedef struct LruCache {
    int size;
    int *array;
} LruCache; 

LruCache* CreateLRU(int size);

LruCache* CreateLRU(int size) {
    LruCache* cache = (LruCache*)malloc(sizeof(LruCache));
    cache->size = size;
    int * Array = (int*)malloc(size*sizeof(int));
    cache->array = Array;
    printf("Cache of size %d created!\n",size);
    return cache;
}   