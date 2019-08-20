#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "hash.h"
#include "linkedList.h"

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
    int size, count;
    Node * head;
    hashtable_t* hash;
    Node * start;
    Node * end;
    int full;
} LruCache; 

// Function declarations
LruCache* CreateLRU(int size);
void putElement(LruCache* cache, int key);
int getNextIndex(LruCache* cache);
int getElement(LruCache* cache,int key);
bool insertIntoHashTable(LruCache* cache, int key, void * data);
char * getCharFromInt(int key);
bool checkCacheForElement(LruCache* cache, char * string);
void removeElementFromHashTable(LruCache* cache, int key);
Node * getElementFromHashTable(LruCache * cache, int key);

// Function implementations
LruCache* CreateLRU(int size) {
    LruCache* cache = (LruCache*)malloc(sizeof(LruCache));
    cache->hash = ht_create(2*size);
    cache->size = size;
    cache->count = 0;
    cache->start = NULL;
    cache->end = NULL;
    cache->full = 0;
    cache->head = NULL;
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
// There are 2 cases of the condition of the cache.
// Full or not full, each of these cases must be 
// handled separately as, if the cache is not full,
// continuous appending to the end of the list is 
// permissive. 
void putElement(LruCache* cache, int key) {
    // The policy here will be insert at "right" of start. 
    bool err;
    if(cache->full==0){
        if(cache->head==NULL){
            cache->head = insertNodeToRight(cache->head,key);
            err = insertIntoHashTable(cache,key,cache->head);
            if(err){
                printf("Key: %d inserted into the hash table.\n", key);
            }else{
                printf("Key: %d already exists in the cache!\n",key);
            }
            cache->start = cache->head;
        }else{
            cache->start = insertNodeToRight(cache->start,key);
            err = insertIntoHashTable(cache,key,cache->start->right);
            if(err){
                printf("Key: %d inserted into the hash table.\n", key);
            }else{
                printf("Key: %d already exists in the cache!\n",key);
            }
            cache->start = cache->start->right;
        }
        cache->count++;
        if(cache->count==cache->size){
            cache->full = 1;
            cache->end = cache->start;
            cache->start = cache->head;
        }
        // The policy here will be changed to insert AT
        // cache->start. That means, insert to right of 
        // start and delete that node.
    }else{
        // If it is the end of the DLL, reposition the
        // start to the head of the DLL.
        if(cache->start==NULL){
            cache->start = cache->head;
        }
        cache->start = insertNodeToRight(cache->start,key);
        err = insertIntoHashTable(cache,key,cache->start->right);
        if(err){
            printf("Key: %d inserted into the hash table.\n", key);
        }else{
            printf("Key: %d already exists in the cache!\n",key);
        }
        
        Node * node = cache->start->right;
        if(node->right==NULL){
            cache->end = node;
        }
        deleteNode(&cache->head,cache->start);
        removeElementFromHashTable(cache,cache->start->key);
        cache->start = node->right;
    }
    if(err){
        printf("Key: %d inserted into the cache.\n",key);
    }
}

// getElement gets the element if it exists in the cache
// A hash map is maintained
// The concept of promoting an element in the cache is 
// implemented here. The promotion is similar to the 
// the concept of eviction in `putElement`, as it replaces
// the LRU element in the cache. 
// The element is removed from its original place, which 
// is obtained from the hash maintained and added at the 
// end of the DLL. All operations happen in O(1) as the 
// pointers to the individual elements are maintained.
int getElement(LruCache* cache,int key) {
    char * string = getCharFromInt(key);
    if(checkCacheForElement(cache,string)){
        // Do the operation of changing the priority
        // only if the current postion is not the 
        // position of the key.
        if(cache->start->key!=key){
            // Remove the element from its old position
            Node * nodeOfKey = getElementFromHashTable(cache,key);
            deleteNode(&cache->head,nodeOfKey);
            // promote the node to the MRU location
            cache->start = insertNodeToLeft(&cache->head,cache->start,key);
        }
        // If the "cache->start" landed on the actual
        // key of the query, we need to move the pointer
        // to the next space in order to proceed.
        else{
            if(cache->start->right!=NULL){
                cache->start = cache->start->right;
            }else{
                cache->start = cache->head;
            }
        }
        return key;
    }else{
        printf("Element doesnt exist in cache!\n");
    }
    return -1;
}

// insertIntoHashTable inserts the key into the hash table
// It is a helper function used as the "hash table insert"
// doesnt take in integers directly
bool insertIntoHashTable(LruCache* cache, int key, void * data){
    char* string = getCharFromInt(key);
    if(!checkCacheForElement(cache,string)){
        ht_put(cache->hash,string,data);
        return true;
    }else{
        return false;
    }
    return true;
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

void removeElementFromHashTable(LruCache* cache, int key){
    char* string = getCharFromInt(key);
    ht_remove(cache->hash,string); 
}

Node * getElementFromHashTable(LruCache * cache, int key){
    char * string = getCharFromInt(key);
    Node * node = ht_get(cache->hash,string);
    return node;
}