package main

import "fmt"

func main() {
	size := 5
	cache := CreateLRU(size)
	fmt.Println(cache.Size)
}
