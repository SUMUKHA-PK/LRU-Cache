package linkedList

import "log"

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
}
