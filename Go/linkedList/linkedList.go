package linkedList

import (
	"fmt"
	"log"
)

// Node is the structure of a single node
type Node struct {
	left  *Node
	right *Node
	key   int
}

// CreateNode returns a newly created node
func CreateNode() *Node {
	return &Node{
		left:  nil,
		right: nil,
		key:   -1,
	}
}

// InsertNodeToLeft inserts a NEW NODE with key
// "keyToInsert" to the left of the node "node"
func InsertNodeToLeft(head **Node, node *Node, keyToInsert int) *Node {
	if node == nil {
		log.Println("The given node was NULL, a new DLL is created and returned.")
		newNode := CreateNode()
		newNode.key = keyToInsert
		return newNode
	}
	// cases to consider are "node->left"
	// being nil and not nil
	if node.left == nil {
		newNode := CreateNode()
		node.left = newNode
		newNode.right = node
		newNode.key = keyToInsert
		if *head == node {
			*head = newNode
			return newNode
		}
	}
	// if ".left" is not nil
	newNode := CreateNode()
	newNode.key = keyToInsert
	leftNode := node.left

	newNode.left = leftNode
	leftNode.right = newNode

	node.left = newNode
	newNode.right = node

	return node
}

// InsertNodeToRight inserts a NEW NODE with key
// "keyToInsert" to the right of the node "node"
func InsertNodeToRight(node *Node, keyToInsert int) *Node {
	if node == nil {
		log.Println("The given node was NULL, a new DLL is created and returned.")
		newNode := CreateNode()
		newNode.key = keyToInsert
		return newNode
	}
	// cases to consider are "node->right"
	// being nil and not nil
	if node.right == nil {
		newNode := CreateNode()
		node.right = newNode
		newNode.left = node
		newNode.key = keyToInsert
		return node
	}
	// if ".right" is not nil
	newNode := CreateNode()
	newNode.key = keyToInsert
	rightNode := node.right

	newNode.right = rightNode
	rightNode.left = newNode

	node.right = newNode
	newNode.left = node

	return node
}

// DeleteNode deletes the node "node"
func DeleteNode(head **Node, node *Node) {
	if node == nil {
		log.Println("Can't delete node, node is nil")
		return
	}

	leftNode := node.left
	rightNode := node.right

	if *head == node {
		if rightNode != nil {
			*head = rightNode
		} else {
			*head = nil
		}
	}

	if leftNode != nil {
		leftNode.right = rightNode
		if rightNode != nil {
			rightNode.left = leftNode
		}
	} else {
		if rightNode != nil {
			rightNode.left = nil
		}
	}
}

// PrintDLL prints the DLL
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
