package linkedList

import (
	"fmt"
	"testing"
)

func TestLinkedList(t *testing.T) {
	var node *Node
	node = InsertNodeToLeft(&node, node, 10)
	if node.key != 10 {
		t.Errorf("Required value 10, got %d", node.key)
	}
	node = InsertNodeToLeft(&node, node, 11)
	node = InsertNodeToLeft(&node, node, 12)
	node = InsertNodeToLeft(&node, node, 13)

	newNode := node.right.right
	newNode = InsertNodeToLeft(&node, newNode, 110)

	PrintDLL(node)
}

func PrintDLL(head *Node) {
	for {
		if head == nil {
			break
		}
		fmt.Printf("%d-> ", head.key)
		head = head.right
	}
	fmt.Println("NULL")
}
