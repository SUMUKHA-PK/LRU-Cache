package main

import "github.com/SUMUKHA-PK/LRU-Cache/Go/linkedList"

// LRUCache is an instance of the cache
// it has the size,count and full which
// indicate the size of the cache, count
// of the variables in the cache and tell
// whether the cache is full(1) or not(0)
// The "Head" pointer is always pointed to
// the head of the Cache DLL and the "Start"
// pointer always points to the next element
// to be replaced. The hashtable maintains
// the mapping of the key to the location
// of the pointer of the node and also is
// helpful for checking existance of the
// elements in the cache.
type LRUCache struct {
	Size, Count, Full int
	Head, Start       *linkedList.Node
	HashTable         map[int]*linkedList.Node
}
