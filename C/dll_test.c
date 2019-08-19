#include<stdio.h>
#include "linkedList.c"

void printDLL(Node * head);
void printDLLRL(Node * head);
void print(Node * head);   

int main(){
    Node* head = createDLL(0);

    for(int i=1;i<3;i++){
        head = insertNodeToRight(head,i);
    }

    Node * node = head->right->right;

    node = insertNodeToRight(node,100);
    node = head->right; 
    node = insertNodeToLeft(&head,node,20);
    print(head);
    deleteNode(&head,head->right->right);
    print(head);
    deleteNode(&head,head);
    print(head);
    return 0;
}

void print(Node * head){
    printDLL(head);
    printDLLRL(head);
}
void printDLL(Node * head){
    while(head!=NULL){
        printf("%d -> ",head->key);
        head=head->right;
    }
    printf(" NULL\n");
}

void printDLLRL(Node * head){
    while(head->right!=NULL){
        head = head->right;
    }

    printf("NULL");
    while(head!=NULL){
        printf(" <-%d",head->key);
        head = head->left;
    }
    printf("\n");
}