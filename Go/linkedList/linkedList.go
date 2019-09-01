package linkedList

import (
	"fmt"
	"log"
)

// Node is the structure of a single node
type Node struct {
	Left  *Node
	Right *Node
	Key   int
}

// CreateNode returns a newly created node
func CreateNode() *Node {
	return &Node{
		Left:  nil,
		Right: nil,
		Key:   -1,
	}
}

// InsertNodeToLeft inserts a NEW NODE with Key
// "KeyToInsert" to the Left of the node "node"
func InsertNodeToLeft(head **Node, node *Node, KeyToInsert int) *Node {
	if node == nil {
		log.Println("The given node was NULL, a new DLL is created and returned.")
		newNode := CreateNode()
		newNode.Key = KeyToInsert
		return newNode
	}
	// cases to consider are "node->Left"
	// being nil and not nil
	if node.Left == nil {
		newNode := CreateNode()
		node.Left = newNode
		newNode.Right = node
		newNode.Key = KeyToInsert
		if *head == node {
			*head = newNode
			return newNode
		}
	}
	// if ".Left" is not nil
	newNode := CreateNode()
	newNode.Key = KeyToInsert
	LeftNode := node.Left

	newNode.Left = LeftNode
	LeftNode.Right = newNode

	node.Left = newNode
	newNode.Right = node

	return node
}

// InsertNodeToRight inserts a NEW NODE with Key
// "KeyToInsert" to the Right of the node "node"
func InsertNodeToRight(node *Node, KeyToInsert int) *Node {
	if node == nil {
		log.Println("The given node was NULL, a new DLL is created and returned.")
		newNode := CreateNode()
		newNode.Key = KeyToInsert
		return newNode
	}
	// cases to consider are "node->Right"
	// being nil and not nil
	if node.Right == nil {
		newNode := CreateNode()
		node.Right = newNode
		newNode.Left = node
		newNode.Key = KeyToInsert
		return node
	}
	// if ".Right" is not nil
	newNode := CreateNode()
	newNode.Key = KeyToInsert
	RightNode := node.Right

	newNode.Right = RightNode
	RightNode.Left = newNode

	node.Right = newNode
	newNode.Left = node

	return node
}

// DeleteNode deletes the node "node"
func DeleteNode(head **Node, node *Node) {
	if node == nil {
		log.Println("Can't delete node, node is nil")
		return
	}

	LeftNode := node.Left
	RightNode := node.Right

	if *head == node {
		if RightNode != nil {
			*head = RightNode
		} else {
			*head = nil
		}
	}

	if LeftNode != nil {
		LeftNode.Right = RightNode
		if RightNode != nil {
			RightNode.Left = LeftNode
		}
	} else {
		if RightNode != nil {
			RightNode.Left = nil
		}
	}
}

// PrintDLL prints the DLL
func PrintDLL(head *Node) {
	for {
		if head == nil {
			break
		}
		fmt.Printf("%d-> ", head.Key)
		head = head.Right
	}
	fmt.Println("NULL")
}
