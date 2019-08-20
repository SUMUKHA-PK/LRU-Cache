package linkedList

import (
	"testing"
)

func TestLinkedList(t *testing.T) {
	var node *Node
	node = InsertNodeToRight(node, 10)
	if node.key != 10 {
		t.Errorf("Required value 10, got %d", node.key)
	}
	node = InsertNodeToRight(node, 11)
	node = InsertNodeToRight(node, 12)
	node = InsertNodeToRight(node, 13)
	PrintDLL(node)
	newNode := node.right.right
	newNode = InsertNodeToRight(newNode, 110)
	PrintDLL(node)
	DeleteNode(&node, node)

	PrintDLL(node)

	InsertNodeToLeft(&node, node, 2)
	PrintDLL(node)
}
