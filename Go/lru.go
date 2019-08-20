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
func CreateLRU(size int) LRUCache {
	cache := newCache(size)
	fmt.Printf("Cache of size %d created\n", cache.Size)
	return cache
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
func PutElement(cache LRUCache, key int) {
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
		cache.Size = linkedList.InsertNodeToRight(cache.Start, key)
		err := insertIntoHashTable(cache, key, cache.Start.Right)
		if err != nil {
			log.Println("Element already exists in the cache!")
			return
		}
		log.Printf("Key: %d entered to the hash table.\n", key)

		node := cache.Start.Right
		linkedList.DeleteNode(&cache.Head, cache.Start)
		cache.HashTable[key] = nil
		cache.Start = node.Right
	}
	log.Printf("Key: %d inserted into the cache\n", key)
}

// insertIntoHashTable inserts the data into the
// hash table. Returns error if the element already
// exists in the hash table.
func insertIntoHashTable(cache LRUCache,
	key int,
	data *linkedList.Node,
) error {
	if _, ok := cache.HashTable[key]; !ok {
		cache.HashTable[key] = data
	} else {
		return errors.New("element exists in cache")
	}
	return nil
}
