package main

import (
	"errors"
	"fmt"
	"log"

	"github.com/SUMUKHA-PK/LRU-Cache/Go/linkedList"
)

func newCache(size int) LRUCache {
	return LRUCache{
		Size:      size,
		Count:     0,
		Full:      0,
		Head:      nil,
		Start:     nil,
		HashTable: newHashTable(),
	}
}

func newHashTable() map[int]*linkedList.Node {
	return make(map[int]*linkedList.Node)
}

// CreateLRU returns an instance of the cache
func CreateLRU(size int) *LRUCache {
	cache := newCache(size)
	fmt.Printf("Cache of size %d created\n", cache.Size)
	return &cache
}

// PutElement adds an element on to the cache.
// Adding an element to the cache makes it the
// newest element in cache. This is "addressed"
// by appending it to the end of the queue.
// The end of the queue is always "addressed" by
// the location of the "start" pointer in the cache.
// In case the current cache is completely full,
// it must evict the LRU element from the cache.
// The eviction of the LRU item happens inherently
// as the "start" pointer is positioned right before
// the LRU element always after a particular operation
// (put or get) has been completed.
// There are 2 cases of the condition of the cache.
// Full or not full, each of these cases must be
// handled separately as, if the cache is not full,
// continuous appending to the end of the list is
// permissive.
func PutElement(cache *LRUCache, key int) {
	log.Printf("Put operation. Key %d\n", key)
	if cache.Full == 0 {
		if cache.Head == nil {
			cache.Head = linkedList.InsertNodeToRight(cache.Head, key)
			err := insertIntoHashTable(cache, key, cache.Head)
			if err != nil {
				log.Println("Element already exists in the cache!")
				return
			}
			log.Printf("Key: %d entered to the hash table.\n", key)
			// The initial setting of the cache.start
			// pointer
			cache.Start = cache.Head
		} else {
			cache.Start = linkedList.InsertNodeToRight(cache.Start, key)
			err := insertIntoHashTable(cache, key, cache.Start.Right)
			if err != nil {
				log.Println("Element already exists in the cache!")
				return
			}
			log.Printf("Key: %d entered to the hash table.\n", key)
			cache.Start = cache.Start.Right
		}
		cache.Count++
		if cache.Count == cache.Size {
			cache.Full = 1
			cache.Start = cache.Head
		}
		// The policy here will be changed to insert AT
		// cache->start. That means, insert to right of
		// start and delete that node.
	} else {
		// If it is the end of the DLL, reposition the
		// start to the head of the DLL
		if cache.Start == nil {
			cache.Start = cache.Head
		}
		cache.Start = linkedList.InsertNodeToRight(cache.Start, key)
		err := insertIntoHashTable(cache, key, cache.Start.Right)
		if err != nil {
			log.Println("Element already exists in the cache!")
			return
		}
		log.Printf("Key: %d entered to the hash table.\n", key)

		node := cache.Start.Right
		linkedList.DeleteNode(&cache.Head, cache.Start)
		delete(cache.HashTable, cache.Start.Key)
		// cache.HashTable[cache.Start.Key] = nil
		cache.Start = node.Right
	}
	log.Printf("Key: %d inserted into the cache\n", key)
}

// GetElement gets the element if it exists in the cache
// A hash map is maintained
// The concept of promoting an element in the cache is
// implemented here. The promotion is similar to the
// the concept of eviction in `putElement`, as it replaces
// the LRU element in the cache.
// The element is removed from its original place, which
// is obtained from the hash maintained and added at the
// end of the DLL. All operations happen in O(1) as the
// pointers to the individual elements are maintained.
func GetElement(Cache *LRUCache, key int) int {
	log.Printf("Get operation. Key %d\n", key)
	var returnValue int
	// check whether the element exists in the cache
	// enters if block if it finds an element.
	if _, ok := Cache.HashTable[key]; ok {
		// Do the operation of changing the priority
		// only if the current postion is not the
		// position of the key.
		if Cache.Start.Key != key {
			// Remove the element from its old position
			nodeOfKey := Cache.HashTable[key]
			linkedList.DeleteNode(&Cache.Head, nodeOfKey)
			// promote the node to the MRU location
			Cache.Start = linkedList.InsertNodeToLeft(&Cache.Head, Cache.Start, key)
		} else {
			// If the "Cache.Start" landed on the actual
			// key of the query, we need to move the pointer
			// to the next space in order to proceed.
			if Cache.Start.Right != nil {
				Cache.Start = Cache.Start.Right
			} else {
				Cache.Start = Cache.Head
			}
		}
		log.Printf("Key: %d retrieved from the cache\n", key)
		returnValue = key
	} else {
		fmt.Printf("Element doesnt exist in cache!\n")
		returnValue = -1
	}
	return returnValue
}

// insertIntoHashTable inserts the data into the
// hash table. Returns error if the element already
// exists in the hash table.
func insertIntoHashTable(cache *LRUCache,
	key int,
	data *linkedList.Node,
) error {
	// check whether the element exists in the cache
	// enters the if block if the element doesnt exist.
	if _, ok := cache.HashTable[key]; !ok {
		cache.HashTable[key] = data
	} else {
		return errors.New("element exists in cache")
	}
	return nil
}

// PrintCache prints the entire content of the cache
func PrintCache(Cache *LRUCache) {
	fmt.Println("Cache:")
	linkedList.PrintDLL(Cache.Head)
	if Cache.Start != nil {
		fmt.Printf("\n\nStart: %d\nFull? : %d\n", Cache.Start.Key, Cache.Full)
	} else {
		fmt.Printf("\n\nStart: %d\nFull? : %d\n", -1, Cache.Full)
	}
	fmt.Printf("\n\n-------------------------------------\n\n")
}
