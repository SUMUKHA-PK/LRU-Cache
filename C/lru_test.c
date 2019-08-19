// Test file includes a few basic tests for the LRU cache
// This file uses the library of functions for using an LRU cache

#include<stdio.h> 
#include "lru.c" 
#include "linkedList.h"

void printCacheCharacteristics(LruCache* cache);

int main() {
    int size = 5;
    LruCache* cache = CreateLRU(size);
    for(int i=0;i<size*3-2;i++){
        putElement(cache,i);
        printCacheCharacteristics(cache);
    }
    printf("\nInserting done\n\n");
    // // for(int i=0;i<size*2;i++){
        printf("%d ",getElement(cache,12));
        printCacheCharacteristics(cache);
        putElement(cache,13);
        printCacheCharacteristics(cache);
        
        printf("%d ",getElement(cache,2));
        printCacheCharacteristics(cache);
    //     printf("%d ",getElement(cache,8));
    //     printCacheCharacteristics(cache);
    //     printf("%d ",getElement(cache,7));
    //     printCacheCharacteristics(cache);
    //     printf("%d ",getElement(cache,8));
    //     printCacheCharacteristics(cache);
    //     printf("%d ",getElement(cache,9));
    //     printCacheCharacteristics(cache);
    //     printf("%d ",getElement(cache,8));
    //     printCacheCharacteristics(cache);
    // // }
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
