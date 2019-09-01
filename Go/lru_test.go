package main

import (
	"fmt"
	"testing"
)

func TestLRUCache(t *testing.T) {
	size := 2
	cache := CreateLRU(size)

	PutElement(cache, 1)
	PrintCache(cache)
	PutElement(cache, 2)
	PrintCache(cache)
	GetElement(cache, 1)
	PrintCache(cache)

	PutElement(cache, 3)
	PrintCache(cache)
	GetElement(cache, 2)
	PrintCache(cache)

	PutElement(cache, 4)
	PrintCache(cache)
	GetElement(cache, 1)
	PrintCache(cache)

	GetElement(cache, 3)
	PrintCache(cache)
	GetElement(cache, 4)
	PrintCache(cache)

	fmt.Println("Complete!")
}
