/******************************************************************************
 * PROGRAM: Binary Search Tree (BST) – Iterative Insert + In-Order Traversal
 * 
 * COURSE: Data Structures and Algorithms (DSA)
 * TOPIC: Trees, Dynamic Linked Structures, Pointer-to-Pointer Manipulation
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 20, 2025
 * VERSION: 1.0
 * 
 *****************************************************************************
 * PROGRAM DESCRIPTION:
 * This program implements a Binary Search Tree (BST) in C using a dynamic
 * linked structure. Each node contains:
 *      - an integer data field
 *      - a pointer to the left child
 *      - a pointer to the right child
 *
 * The BST is **not** a linear linked list. Rather, each node uses **two links** 
 * (left and right child pointers), forming a hierarchical, non-linear structure.
 *
 * INSERTION METHOD:
 *  - Implemented using an **iterative approach**
 *  - Uses **pointer-to-pointer traversal (`BST *trav`)**
 *  - Ensures correct placement without recursion
 *
 * PARAMETERS / DATA BEING PASSED:
 *  - `Insert(BST *B, int val)`
 *      • B  → pointer to the root (or subtree pointer)  
 *      • val → integer value to be inserted  
 *
 *  - `inorder(BST B)`
 *      • B  → pointer to current node for traversal  
 *
 * SUPPORTED OPERATIONS:
 *   1. insert()     : Inserts integer values into the BST (iteratively)
 *   2. inorder()    : Performs in-order traversal (Left, Root, Right)
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node * left;
    struct node * right;
}Node, *BST;


void Insert(BST * B, int val);
void Delete(BST * B, int val);
    // either left node of the child of the node to be deleted
    // or left most node(most minimum) of the right subtree 
Node * findMin(BST B);
void inorder(BST B);
void postorder(BST B);
void preorder(BST B);

int main(){
    BST abc =NULL;
    
    Insert(&abc, 10);
    Insert(&abc, 5);
    Insert(&abc, 15);
    Insert(&abc, 3);
    Insert(&abc, 7);

    printf("In-order traversal of BST: ");
    inorder(abc);
    printf("\n\n");
    printf("Post-order traversal of BST: ");
    postorder(abc);
    printf("\n\n");
    printf("Pre-order traversal of BST: ");
    preorder(abc);
    printf("\n\n");
    
    Delete(&abc, 5);
    printf("\n\n");
    printf("\n\n");

    printf("In-order traversal of BST: ");
    inorder(abc);
    printf("\n\n");
    printf("Post-order traversal of BST: ");
    postorder(abc);
    printf("\n\n");
    printf("Pre-order traversal of BST: ");
    preorder(abc);
    printf("\n\n");
    
    
    return 0;
}

void Insert(BST * B, int val){
    
    BST * trav = B;


    while(*trav !=NULL){
        if(val < (*trav)->data) trav = &(*trav)->left;
        else if(val > (*trav)->data) trav = &(*trav)->right;
        else return; //duplicates
    }
    
    Node *temp = malloc(sizeof(Node));
    temp->data = val;
    temp->left = temp->right = NULL; 
    *trav =  temp;
   
    
    
    
    /*
    BST * trav = B;
    
    while(*trav != NULL && (*trav)->data != val){
        if(val < (*trav)->data)         trav = &(*trav)->left;
        else if (val > (*trav)->data)        trav = &(*trav)->right;
    }
    if(*trav == NULL){
        *trav = (BST) calloc(1, sizeof(Node));
        (*trav)->data = val;
    }
    
    
    */
    
    /*
    other VERSION
    Node *temp = malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL;
    trav->data = val;
    *trav = temp;
    */
}



void Delete(BST * B, int val){
    Node * temp;

    if(*B == NULL) return;

    else if(val < (*B)->data) Delete(&(*B)->left, val);
    else if(val > (*B)->data) Delete(&(*B)->right, val);
    else{       //found condition
        if((*B)->left && (*B)->right){
            temp = findMin((*B)->right);
            (*B)->data = temp->data;
            Delete(&(*B)->right, (*B)->data);
        }else{
            temp = *B;
            if((*B)->left == NULL) *B = (*B)->right;
            else *B = (*B)->left;
            free(temp);
        }
        
    }
}

//recursive implementation
Node * findMin(BST B){
    if(B == NULL)return NULL;
    while(B->left != NULL) B = B->left;
    return B;
}
//nonrecursive
/*
Node * findMax(BST B){
    if(B == NULL) return NULL;
    while(B->right != NULL) B = B->right;
    return B;
}
*/






void inorder(BST B){
    if(B == NULL) return;
    inorder(B->left);
    printf("%d ", B->data);
    inorder(B->right);

}
void postorder(BST B){
    if(B == NULL) return;
    postorder(B->left);
    postorder(B->right);
    printf("%d ", B->data);
}void preorder(BST B){
    if(B == NULL) return;
    printf("%d ", B->data);
    preorder(B->left);
    preorder(B->right);
}