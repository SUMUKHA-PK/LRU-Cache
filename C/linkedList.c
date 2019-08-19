// Following is the implementation of a 
// Doubly Linked List(DLL) in C.

#include<stdio.h>
#include<stdlib.h>

// This struct is the representation of 
// a single node of the DLL
typedef struct node {
    struct node * left;
    struct node * right;
    int key;
} Node;

// Function declarations
Node * createNode();
Node * createDLL(int headKeyVal);
Node * insertNodeToLeft(Node ** head, Node * node, int keyToInsert);
Node * insertNodeToRight(Node * node, int keyToInsert);
void deleteNode(Node ** head, Node * node);

// Function implementations

// createNode creates a node of the DLL
Node * createNode(){
    Node * node = (Node*)malloc(sizeof(struct node));
    node->left = NULL;
    node->right = NULL;
    node->key = -1;
    return node;
}

// createDLL creates a new DLL with value
// passed to the function as the value of
// the head node of the DLL
Node * createDLL(int headKeyVal){
    Node * head = createNode();
    head->key = headKeyVal;
    return head;
}

// insertNodeToLeft inserts a NEW NODE with key 
// "keyToInsert" to the left of the node "node"
Node * insertNodeToLeft(Node ** head, Node * node, int keyToInsert){
    if(node==NULL){
        printf("The given node was NULL, a new DLL is created and returned.\n");
        return createDLL(keyToInsert);
    }
    // cases to consider are "node->left" 
    // being NULL and not NULL
    if(node->left == NULL){
        Node * newNode = createNode(); 
        node->left = newNode;
        newNode->right = node;
        newNode->key = keyToInsert;
        if(*head==node){
            *head = newNode;
            // return newNode as the head is now
            // changed to the newNode and the head
            // is confirmed to be the newNode
            return newNode;
        }
    }
    // if ->left is not NULL
    Node * newNode = createNode();
    newNode->key = keyToInsert;
    Node * leftNode = node ->left;
    
    newNode->left = leftNode;
    leftNode->right = newNode;

    node->left = newNode;
    newNode->right = node;

    return node;
}

// insertNodeToRight inserts a NEW NODE with key 
// "keyToInsert" to the right of the node "node".
Node * insertNodeToRight(Node * node, int keyToInsert){
    if(node==NULL){
        return createDLL(keyToInsert);
    }
    // cases to consider are "node->right"
    // being NULL and not NULL
    if(node->right==NULL){
        Node * newNode = createNode();
        node->right = newNode;
        newNode ->left = node;
        newNode->key = keyToInsert;
        return node;
    }
    // If ->right is not NULL
    Node * newNode = createNode();
    newNode->key = keyToInsert;
    Node * rightNode = node->right;

    newNode->right = rightNode;
    rightNode->left = newNode;

    node->right = newNode;
    newNode->left = node;
    
    return node;
}

// deleteNode deletes the node "node"
// "*head" is a parameter to ensure deletion 
// of head nodes
void deleteNode(Node ** head, Node * node){
    if(node==NULL){
        printf("Can't delete node, node is NULL\n");
        return;
    }
    Node * leftNode = node->left;
    Node * rightNode = node->right;

    if(*head==node){
        if(rightNode!=NULL){
            *head = rightNode;
        }else{
            *head = NULL;
        }
    }
    // 4 cases
    if(leftNode!=NULL){
        leftNode->right = rightNode;
        if(rightNode!=NULL){
            rightNode->left = leftNode;
        }
    }else{
        if(rightNode!=NULL){
            rightNode->left = NULL;
        }
    }
    free(node);
}