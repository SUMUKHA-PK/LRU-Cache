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
    int start,end;
} LruCache; 

// Function declarations
LruCache* CreateLRU(int size);
void putElement(LruCache* cache, int key);
int getNextIndex(LruCache* cache);
int getElement(LruCache* cache,int key);
bool insertIntoHashTable(LruCache* cache, int key);
char * getCharFromInt(int key);
bool checkCacheForElement(LruCache* cache, char * string);

// Function implementations
LruCache* CreateLRU(int size) {
    LruCache* cache = (LruCache*)malloc(sizeof(LruCache));
    cache->hash = ht_create(2*size);
    cache->size = size;
    cache->start = 0;
    cache->end = -1;
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
// This is automatically done as, when the cache
// is full, the LRU element would be the "next"
// of the "end" pointer.
void putElement(LruCache* cache, int key) {
    int index = getNextIndex(cache);
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

// getNextIndex returns the next empty index to enter the element to
int getNextIndex(LruCache* cache){
    if(cache->end == cache->size -1){
        cache->end = 0;
    }else{
        cache->end++;
    }
    return cache->end;
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