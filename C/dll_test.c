#include<stdio.h>
#include "linkedList.h"
  
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

