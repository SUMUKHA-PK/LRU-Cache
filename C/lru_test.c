// Test file includes a few basic tests for the LRU cache
// This file uses the library of functions for using an LRU cache

#include<stdio.h> 
#include "lru.c" 
#include "linkedList.h"

void printCacheCharacteristics(LruCache* cache);

int main() {
    int size = 2;
    LruCache* cache = CreateLRU(size);
    
    putElement(cache,1);
    printCacheCharacteristics(cache);
    putElement(cache,2);
    printCacheCharacteristics(cache);
    getElement(cache,1);
    printCacheCharacteristics(cache);
    
    putElement(cache,3);
    printCacheCharacteristics(cache);
    getElement(cache,2);
    printCacheCharacteristics(cache);
    
    putElement(cache,4);
    printCacheCharacteristics(cache);
    getElement(cache,1);
    printCacheCharacteristics(cache);

    getElement(cache,3);
    printCacheCharacteristics(cache);
    getElement(cache,4);
    printCacheCharacteristics(cache);

    printf("Complete!\n");
    return 0;
}

void printCacheCharacteristics(LruCache* cache){
    printf("\n\nCache:\n\t");
    printDLL(cache->head);
    if(cache->start!=NULL&&cache->end!=NULL){
        printf("\n\nStart: %d\nEnd: %d\nFull? : %d\n",cache->start->key,cache->end->key,cache->full);
    }else{
        printf("\n\nStart: %d\nEnd: %d\nFull? : %d\n",-1,-1,cache->full);
    }
    printf("\n\n-------------------------------------\n\n");
}
