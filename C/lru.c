#include<stdio.h>
#include<stdlib.h>
#include<C/hash.h>

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
    hashtable_t* hash;
    int start,end;
} LruCache; 

// Function declarations
LruCache* CreateLRU(int size);
void putElement(LruCache* cache, int key);
int getNextIndex(LruCache* cache);

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
    insertIntoHashTable(cache,key);
    cache->array[index] = key;
}

// getElement gets the element if it exists in the cache
// A hash map is maintained 
int getElement(LruCache* cache,int key) {
    if(checkKeyInHashTable(cache,key)){

    }else{
        printf("Element doesnt exist in cache!\n");
    }
}

// insertIntoHashTable inserts the key into the hash table
// It is a helper function used as the "hash table insert"
// doesnt take in integers directly
void insertIntoHashTable(LruCache* cache, int key){

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