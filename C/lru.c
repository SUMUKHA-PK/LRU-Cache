#include<stdio.h>
#include<stdlib.h>
#include "hash.h"
#include<stdbool.h>

// The idea of implementation of LRU cache is,
// everytime a new object is "called", its usage
// is "addressed" by moving it up the "stack"
// The above operation is done because, to maintain
// the LRU object, we need to maintain an order of 
// the LRU objects so that once the LRU object is 
// used, the next RU object becomes the LRU objects
// The "start" pointer is always at the LRU element.
// The "end" pointer is always at the most recent element.

// The LRU Cache object
// It contains the size of the cache and the
// pointer to the first element of the cache
// All elements are inserted at the "start"
// index and "end" pointer "pushes" the "start"
// pointer from behind and moves them forward
// in a circular manner.
typedef struct LruCache {
    int size;
    int *array;
    hashtable_t* hash;
    int start,end,full;
} LruCache; 

// Function declarations
LruCache* CreateLRU(int size);
void putElement(LruCache* cache, int key);
int getNextIndex(LruCache* cache);
int getElement(LruCache* cache,int key);
bool insertIntoHashTable(LruCache* cache, int key);
char * getCharFromInt(int key);
bool checkCacheForElement(LruCache* cache, char * string);
void removeElementFromCache(LruCache* cache, int key);

// Function implementations
LruCache* CreateLRU(int size) {
    LruCache* cache = (LruCache*)malloc(sizeof(LruCache));
    cache->hash = ht_create(2*size);
    cache->size = size;
    cache->start = -1;
    cache->end = -1;
    cache->full = 0;
    int * Array = (int*)malloc(size*sizeof(int));
    cache->array = Array;
    printf("Cache of size %d created!\n",size);
    return cache;
}   

// putElement adds an element on to the cache
// Adding an element to the cache makes it the 
// newest element in cache. This is "addressed"
// by appending it to the end of the queue.
// In case the current cache is completely full, 
// it must evict the LRU element from the cache.
// The eviction of the LRU item happens inherently
// as the "start" pointer is positioned at the 
// LRU element always after a particular operation
// (put or get) has been completed. 
void putElement(LruCache* cache, int key) {
    int index = getNextIndex(cache);    
    if(index == cache->size-1){
        cache->full = 1;
    }
    if (cache->full==1){
        int currElement = cache->array[index];
        removeElementFromCache(cache,currElement);
    }
    bool err = insertIntoHashTable(cache,key);
    if(!err){
        printf("Element already exists in the cache!\n");
        return;
    }
    cache->array[index] = key;
    printf("%d added to cache\n",key);
}

// getElement gets the element if it exists in the cache
// A hash map is maintained
// The concept of promoting an element in the cache is 
// implemented here. The promotion is similar to the 
// the concept of eviction in `putElement`, as it replaces
// the LRU element in the cache. 
int getElement(LruCache* cache,int key) {
    char * string = getCharFromInt(key);
    if(checkCacheForElement(cache,string)){

        return key;
    }else{
        printf("Element doesnt exist in cache!\n");
    }
    return -1;
}

// insertIntoHashTable inserts the key into the hash table
// It is a helper function used as the "hash table insert"
// doesnt take in integers directly
bool insertIntoHashTable(LruCache* cache, int key){
    char* string = getCharFromInt(key);
    if(!checkCacheForElement(cache,string)){
        ht_put(cache->hash,string,"");
        return true;
    }else{
        return false;
    }
    return true;
}

// getNextIndex returns the place of insertion of 
// next element to the cache. It always is the point
// where "cache->start" exists or is "wished/hoped" 
// to exist. This function always positions the "start"
// pointer to the desired position.
int getNextIndex(LruCache* cache){
    // Wrap around condition
    if(cache->start == cache->size -1){
        cache->start = 0;
        cache->end = cache->size-1;
    }else{
        // If its the first operation of the cache,
        // only the "start" pointer must move.
        if(cache->start==0&&cache->end==0){
            cache->end --;
        }
        // Since there is no wrap around, the 
        // pointer normally moves forward.
        cache->start++;
        // Checking for wrap around of the "end" pointer
        if(cache->end == cache->size -1){
            cache->end = 0;
        }else{
            cache->end ++;
        }
    }
    return cache->start;
}

char* getCharFromInt(int key){
    char * string = (char *)malloc(sizeof(char)*100);
    sprintf(string,"%d",key);
    return (char *)string;
}

// checkCacheForElement :
//                          returns false if the element doesnt exist
//                          returns true if the element is in the cache
bool checkCacheForElement(LruCache* cache, char * string){
    if(ht_get(cache->hash,string)==NULL){
        return false;
    }
    return true;
}

void removeElementFromCache(LruCache* cache, int key){
    char* string = getCharFromInt(key);
    ht_remove(cache->hash,string); 
    printf("%d evicted from cache!\n",key);
}