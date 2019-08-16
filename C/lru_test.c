// Test file includes a few basic tests for the LRU cache
// This file uses the library of functions for using an LRU cache
#include<stdio.h> 
#include "lru.c" 

int main() {
    int size = 5;
    LruCache* cache = CreateLRU(size);
    for(int i=0;i<size*2;i++){
        putElement(cache,i);
    }
    printf("\n");
    for(int i=0;i<size*2;i++){
        printf("%d ",getElement(cache,i));
    }
    printf("\n");
    return 0;
}