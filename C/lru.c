#include<stdio.h>
#include<stdlib.h>

// The idea of implementation of LRU cache is,
// everytime a new object is "called", its usage
// is "addressed" by moving it up the "stack"
// The above operation is done because, to maintain
// the LRU object, we need to maintain an order of 
// the LRU objects so that once the LRU object is 
// used, the next RU object becomes the LRU objects

// The LRU Cache object
// It contains the size of the cache and the
// pointer to the first element of the cache
typedef struct LruCache {
    int size;
    int *array;
    int start,end;
} LruCache; 

// Function declarations
LruCache* CreateLRU(int size);
void putElement(LruCache* cache, int key);
int getNextIndex(LruCache* cache);

// Function implementations
LruCache* CreateLRU(int size) {
    LruCache* cache = (LruCache*)malloc(sizeof(LruCache));
    cache->size = size;
    cache->start = 0;
    cache->end = -1;
    int * Array = (int*)malloc(size*sizeof(int));
    cache->array = Array;
    printf("Cache of size %d created!\n",size);
    return cache;
}   

// putElement adds an element on to the cache
void putElement(LruCache* cache, int key) {
    int index = getNextIndex(cache);
    cache->array[index] = key;
    cache->end ++;
}

// getNextIndex returns the next empty index to enter the element to
int getNextIndex(LruCache* cache){
    int index;
    if(cache->end == cache->size -1){
        return 0;
    }else{
        return cache->end + 1;
    }
    return index;
}