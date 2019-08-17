// Test file includes a few basic tests for the LRU cache
// This file uses the library of functions for using an LRU cache
#include<stdio.h> 
#include "lru.c" 

void printCacheCharacteristics(LruCache* cache);

int main() {
    int size = 5;
    LruCache* cache = CreateLRU(size);
    for(int i=0;i<size*2;i++){
        putElement(cache,i);
        printCacheCharacteristics(cache);
    }
    printf("\n");
    for(int i=0;i<size*2;i++){
        printf("%d ",getElement(cache,i));
    }
    printf("\n");
    return 0;
}

void printCacheCharacteristics(LruCache* cache){
    printf("\n\nCache:\n\t");
    for(int i=0;i<cache->size;i++){
        printf("%d ",cache->array[i]);
    }
    printf("\n\nStart: %d\nEnd: %d\nFull? : %d\n",cache->start,cache->end,cache->full);
    printf("\n\n-------------------------------------\n\n");
}