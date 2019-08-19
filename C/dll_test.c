#include<stdio.h>
#include "linkedList.c"

void printDLL(Node * head);

int main(){
    Node* head = createDLL(0);

    for(int i=1;i<3;i++){
        head = insertNodeToLeft(&head,head,i);
    }
    head->right->right = insertNodeToLeft(&head,head->right->right,100);
    printDLL(head);

    return 0;
}

void printDLL(Node * head){
    while(head!=NULL){
        printf("%d -> ",head->key);
        head=head->right;
    }
    printf(" NULL\n");
}