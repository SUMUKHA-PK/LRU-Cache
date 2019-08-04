package main

import "fmt"

func newCache(size int) LRUCache {
	return LRUCache{
		Size:  size,
		Cache: make([]int, size),
	}
}

// CreateLRU returns an instance of the cache
func CreateLRU(size int) LRUCache {
	cache := newCache(size)
	fmt.Printf("Cache of size %d created\n", cache.Size)
	return cache
}
